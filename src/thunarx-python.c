/*-
 * Copyright (c) 2009 Adam Plumb <adamplumb@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <Python.h>
#include <pygobject.h>
#include <gmodule.h>
#include <gtk/gtk.h>

#include "thunarx-python.h"
#include "thunarx-python-object.h"

static const GDebugKey thunarx_python_debug_keys[] = {
  {"all", THUNARX_PYTHON_DEBUG_ALL},
};
static const guint thunarx_python_ndebug_keys = sizeof (thunarx_python_debug_keys) / sizeof (GDebugKey);
ThunarxPythonDebug thunarx_python_debug;

static GArray *all_types = NULL;

G_MODULE_EXPORT void thunar_extension_initialize (ThunarxProviderPlugin *plugin);
G_MODULE_EXPORT void thunar_extension_shutdown (void);
G_MODULE_EXPORT void thunar_extension_list_types (const GType **types, gint *n_types);

static gboolean thunarx_python_init_pygobject (void);
static gboolean thunarx_python_init_python (void);


static inline gboolean 
thunarx_python_init_pygobject(void) {
    PyObject *gobject = pygobject_init (3, 0, 0);

    if (gobject == NULL) {
        PyErr_Print ();
        return FALSE;
    }

    return TRUE;
}


static gboolean 
thunarx_python_init_python (void) {
    PyObject *thunarx;
    GModule *libpython;

    debug_enter();

    if (Py_IsInitialized())
        return TRUE;
    
    debug("Setting GI_TYPELIB_PATH to " GI_TYPELIB_PATH);
    gchar *typelib_env = g_strdup_printf("GI_TYPELIB_PATH=$GI_TYPELIB_PATH:%s", GI_TYPELIB_PATH);
    putenv(typelib_env);

    debug ("g_module_open " PY_LIB_LOC "/lib" PYTHON_LIB_NAME "." G_MODULE_SUFFIX ".1.0");  
    libpython = g_module_open (PY_LIB_LOC "/lib" PYTHON_LIB_NAME "." G_MODULE_SUFFIX ".1.0", 0);
    if (!libpython) {
        g_warning ("g_module_open libpython failed: %s", g_module_error());
    }

    debug ("Py_Initialize");
    Py_Initialize();
    if (PyErr_Occurred()) {
        PyErr_Print();
        return FALSE;
    }

    debug ("PySys_SetArgv");
#if PY_MAJOR_VERSION >= 3
    wchar_t *argv[] = { L"thunar", NULL };
#else
    char *argv[] = { "thunar", NULL };
#endif
    PySys_SetArgv (1, argv);
    if (PyErr_Occurred()) {
        PyErr_Print();
        return FALSE;
    }

    debug("Sanitize the python search path");
    PyRun_SimpleString("import sys; sys.path = [path for path in sys.path if path]");
    if (PyErr_Occurred()) {
        PyErr_Print();
        return FALSE;
    }

    /* import gobject */
    debug("init_pygobject");
    if (!thunarx_python_init_pygobject()) {
        g_warning("pygobject initialization failed");
        return FALSE;
    }

    g_setenv("INSIDE_THUNARX_PYTHON", "", FALSE);
    debug("import Thunarx");
    PyRun_SimpleString("import gi; gi.require_version('Thunarx', '3.0')");
    thunarx = PyImport_ImportModule("gi.repository.Thunarx");
    if (!thunarx) {
        PyErr_Print();
        return FALSE;
    }
        
    _PyGtkWidget_Type = pygobject_lookup_class(GTK_TYPE_WIDGET);
    g_assert(_PyGtkWidget_Type != NULL);

#define IMPORT(x, y) \
    _PyThunarx##x##_Type = (PyTypeObject *)PyObject_GetAttrString(thunarx, y); \
    if (_PyThunarx##x##_Type == NULL) { \
        PyErr_Print(); \
        return FALSE; \
    }

    IMPORT(FileInfo, "FileInfo");
    IMPORT(MenuItem, "MenuItem");
    IMPORT(Menu, "Menu");
    IMPORT(MenuProvider, "MenuProvider");
    IMPORT(PreferencesProvider, "PreferencesProvider");
    IMPORT(PropertyPage, "PropertyPage");
    IMPORT(PropertyPageProvider, "PropertyPageProvider");
    IMPORT(ProviderPlugin, "ProviderPlugin");
    IMPORT(Renamer, "Renamer");
    IMPORT(RenamerProvider, "RenamerProvider");
    
#undef IMPORT
  
    return TRUE;
}

static void
thunarx_python_load_file (ThunarxProviderPlugin *plugin, 
                          const gchar           *filename) {
    PyObject *main_module, *main_locals, *locals, *key, *value;
    PyObject *module;
    Py_ssize_t pos = 0;
    GType new_type;

    main_module = PyImport_AddModule("__main__");
    if (main_module == NULL) {
        g_warning ("Could not get __main__");
        return;
    }

    main_locals = PyModule_GetDict(main_module);
    module = PyImport_ImportModuleEx((char *) filename, main_locals, main_locals, NULL);
    if (!module) {
        PyErr_Print();
        return;
    }

    locals = PyModule_GetDict(module);
  
    while (PyDict_Next(locals, &pos, &key, &value)) {
        if (!PyType_Check(value))
            continue;

        if (PyObject_IsSubclass(value, (PyObject*)&PyThunarxMenuProvider_Type) ||
                PyObject_IsSubclass(value, (PyObject*)&PyThunarxPropertyPageProvider_Type) ||
                PyObject_IsSubclass(value, (PyObject*)&PyThunarxPreferencesProvider_Type) ||
                PyObject_IsSubclass(value, (PyObject*)&PyThunarxRenamerProvider_Type)) {
            new_type = thunarx_python_object_get_type(plugin, value);
            g_array_append_val(all_types, new_type);
        }
    }
}

static void
thunarx_python_load_dir (ThunarxProviderPlugin  *plugin, 
                         const char             *dirname) {
    GDir *dir;
    const char *name;
    gboolean initialized = FALSE;

    debug_enter_args("dirname=%s", dirname);
    
    dir = g_dir_open (dirname, 0, NULL);
    if (!dir)
        return;
            
    while ((name = g_dir_read_name(dir))) {
        if (g_str_has_suffix(name, ".py")) {
            char *modulename;
            int len;

            len = strlen(name) - 3;
            modulename = g_new0(char, len + 1);
            strncpy(modulename, name, len);

            if (!initialized) {
                PyObject *sys_path, *py_path;

                /* n-p python part is initialized on demand (or not
                * at all if no extensions are found) */
                if (!thunarx_python_init_python()) {
                    g_warning("thunarx_python_init_python failed");
                    g_dir_close(dir);
                }
                
                /* sys.path.insert(0, dirname) */
                sys_path = PySys_GetObject("path");
#if PY_MAJOR_VERSION >= 3
                py_path = PyUnicode_FromString(dirname);
#else
                py_path = PyString_FromString(dirname);
#endif
                PyList_Insert(sys_path, 0, py_path);
                Py_DECREF(py_path);
            }

            thunarx_python_load_file(plugin, modulename);
        }
    }
}

static void
thunarx_python_check_all_directories(ThunarxProviderPlugin *plugin) {
    gchar *extensions_dir = NULL;

    GList *dirs = NULL;

    // Check ~/.local/share first
    dirs = g_list_append(dirs, g_build_filename(g_get_user_data_dir(), 
        "thunarx-python", "extensions", NULL));

    // If thunar is built in a non-standard prefix
    // Check that' prefix's DATADIR
    gchar *prefix_extension_dir = DATADIR "/thunarx-python/extensions";
    dirs = g_list_append(dirs, prefix_extension_dir);

    // Check all system data dirs 
    const gchar *const *temp = g_get_system_data_dirs();
    while (*temp != NULL) {
        gchar *dir = g_build_filename(*temp,
            "thunarx-python", "extensions", NULL);
        if (dir != prefix_extension_dir) {
            dirs = g_list_append(dirs, dir);
        }

        temp++;
    }

    // Finally, check the old thunarx-python <0.3.0 extension dir
    dirs = g_list_append(dirs, THUNARX_EXTENSION_DIR "/python");

    dirs = g_list_first(dirs);
    while (dirs != NULL) {
        gchar *dir = dirs->data;
        thunarx_python_load_dir(plugin, dir);
        dirs = dirs->next;
    }

    g_list_free(dirs);
}

G_MODULE_EXPORT void
thunar_extension_initialize (ThunarxProviderPlugin *plugin) {
    const gchar *mismatch;
    const gchar *env_string;

    env_string = g_getenv("THUNARX_PYTHON_DEBUG");
    if (env_string != NULL) {
        thunarx_python_debug = g_parse_debug_string(env_string,
                                                     thunarx_python_debug_keys,
                                                     thunarx_python_ndebug_keys);
        env_string = NULL;
    }

    debug_enter();

    /* verify that the thunarx versions are compatible */
    mismatch = thunarx_check_version (THUNARX_MAJOR_VERSION, THUNARX_MINOR_VERSION, THUNARX_MICRO_VERSION);
    if (G_UNLIKELY (mismatch != NULL)) {
        g_warning ("Version mismatch: %s", mismatch);
        return;
    }

    all_types = g_array_new(FALSE, FALSE, sizeof(GType));

    thunarx_provider_plugin_set_resident (plugin, TRUE);

    thunarx_python_check_all_directories(plugin);
}

G_MODULE_EXPORT void
thunar_extension_shutdown (void) {
    debug_enter();

    if (Py_IsInitialized())
        Py_Finalize();

    g_array_free (all_types, TRUE);
}

G_MODULE_EXPORT void
thunar_extension_list_types (const GType **types,
                             gint         *n_types) {
    debug_enter();

    *types = (GType*)all_types->data;
    *n_types = all_types->len;
}
