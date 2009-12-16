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
#include <pygtk/pygtk.h>

#include "thunarx-python.h"
#include "thunarx-python-object.h"

static GArray *all_types = NULL;

G_MODULE_EXPORT void thunar_extension_initialize (ThunarxProviderPlugin *plugin);
G_MODULE_EXPORT void thunar_extension_shutdown (void);
G_MODULE_EXPORT void thunar_extension_list_types (const GType **types, gint *n_types);

static gboolean thunarx_python_init_pygobject (void);
static gboolean thunarx_python_init_pygtk (void);
static gboolean thunarx_python_init_python (void);



static inline gboolean thunarx_python_init_pygobject(void)
{
    PyObject *gobject = PyImport_ImportModule("gobject");
    if (gobject != NULL) {
        PyObject *mdict = PyModule_GetDict(gobject);
        PyObject *cobject = PyDict_GetItemString(mdict, "_PyGObject_API");
        if (PyCObject_Check(cobject))
            _PyGObject_API = (struct _PyGObject_Functions *)PyCObject_AsVoidPtr(cobject);
        else {
            PyErr_SetString(PyExc_RuntimeError,
                            "could not find _PyGObject_API object");
			PyErr_Print();
			return FALSE;
        }
    } else {
        PyErr_Print();
        g_warning("could not import gobject");
        return FALSE;
    }
	return TRUE;
}



static inline gboolean thunarx_python_init_pygtk(void)
{
    PyObject *pygtk = PyImport_ImportModule("gtk._gtk");
    if (pygtk != NULL) {
		PyObject *module_dict = PyModule_GetDict(pygtk);
		PyObject *cobject = PyDict_GetItemString(module_dict, "_PyGtk_API");
		if (PyCObject_Check(cobject))
			_PyGtk_API = (struct _PyGtk_FunctionStruct*)
				PyCObject_AsVoidPtr(cobject);
		else {
            PyErr_SetString(PyExc_RuntimeError,
                            "could not find _PyGtk_API object");
			PyErr_Print();
			return FALSE;
        }
    } else {
        PyErr_Print();
        g_warning("could not import gtk._gtk");
        return FALSE;
    }
	return TRUE;
}



static gboolean 
thunarx_python_init_python (void)
{
	PyObject *pygtk, *mdict, *require;
	PyObject *sys_path, *tmp, *thunarx, *gtk, *pygtk_version, *pygtk_required_version;
  GModule *libpython;
  char *argv[] = { "thunarx", NULL };
  
  debug_enter();

  if (Py_IsInitialized())
    return TRUE;

  debug ("g_module_open " PY_LIB_LOC "/libpython" PYTHON_VERSION "." G_MODULE_SUFFIX);  
  libpython = g_module_open (PY_LIB_LOC "/libpython" PYTHON_VERSION "." G_MODULE_SUFFIX, 0);
  if (!libpython)
    g_warning ("g_module_open libpython failed: %s", g_module_error());
  
  debug ("Py_Initialize");
  Py_Initialize();
  if (PyErr_Occurred())
  {
    PyErr_Print();
    return FALSE;
  }
  
  debug ("PySys_SetArgv");
  PySys_SetArgv (1, argv);
  if (PyErr_Occurred())
  {
    PyErr_Print();
    return FALSE;
  }

	/* pygtk.require("2.0") */
	debug("pygtk.require(\"2.0\")");
	pygtk = PyImport_ImportModule("pygtk");
	if (!pygtk) {
		PyErr_Print();
		return FALSE;
	}
	mdict = PyModule_GetDict(pygtk);
	require = PyDict_GetItemString(mdict, "require");
	PyObject_CallObject(require, Py_BuildValue("(S)", PyString_FromString("2.0")));
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
	/* import gtk */
	debug("init_pygtk");
	if (!thunarx_python_init_pygtk()) {
		g_warning("pygtk initialization failed");
		return FALSE;
	}

	/* gobject.threads_init() */
  debug("pyg_enable_threads");
	setenv("PYGTK_USE_GIL_STATE_API", "", 0);
	pyg_enable_threads();

	/* gtk.pygtk_version < (2, 4, 0) */
	gtk = PyImport_ImportModule("gtk");
	mdict = PyModule_GetDict(gtk);
	pygtk_version = PyDict_GetItemString(mdict, "pygtk_version");
	pygtk_required_version = Py_BuildValue("(iii)", 2, 4, 0);
	if (PyObject_Compare(pygtk_version, pygtk_required_version) == -1) {
		g_warning("PyGTK %s required, but %s found.",
				  PyString_AsString(PyObject_Repr(pygtk_required_version)),
				  PyString_AsString(PyObject_Repr(pygtk_version)));
		Py_DECREF(pygtk_required_version);
		return FALSE;
	}
	Py_DECREF(pygtk_required_version);
  
  debug("sys.path.insert(0, ...)");
  sys_path = PySys_GetObject("path");
  PyList_Insert(sys_path, 0, (tmp = PyString_FromString(THUNARX_LIBDIR "/thunarx-python")));
  Py_DECREF(tmp);
  
  g_setenv("INSIDE_THUNARX_PYTHON", "", FALSE);
  debug("import thunarx");
  thunarx = PyImport_ImportModule("thunarx");
  if (!thunarx)
  {
    PyErr_Print();
    return FALSE;
  }

	/* Extract types and interfaces from thunarx */
	mdict = PyModule_GetDict(thunarx);
	
	_PyGtkWidget_Type = pygobject_lookup_class(GTK_TYPE_WIDGET);
	g_assert(_PyGtkWidget_Type != NULL);

	_PyGtkAction_Type = pygobject_lookup_class(GTK_TYPE_ACTION);
	g_assert(_PyGtkAction_Type != NULL);

#define IMPORT(x, y) \
    _PyThunarx##x##_Type = (PyTypeObject *)PyDict_GetItemString(mdict, y); \
	if (_PyThunarx##x##_Type == NULL) { \
		PyErr_Print(); \
		return FALSE; \
	}

	IMPORT(FileInfo, "FileInfo");
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
thunarx_python_load_file (ThunarxProviderPlugin *plugin, const gchar *filename)
{
  PyObject *main_module, *main_locals, *locals, *key, *value;
  PyObject *module;
  Py_ssize_t pos = 0;
  GType new_type;
  
  main_module = PyImport_AddModule("__main__");
  if (main_module == NULL)
  {
    g_warning ("Could not get __main__");
    return;
  }
  
  main_locals = PyModule_GetDict(main_module);
  g_print("Attempting to load module %s\n", filename);
  module = PyImport_ImportModuleEx((char *) filename, main_locals, main_locals, NULL);
  if (!module)
  {
    PyErr_Print();
    return;
  }
  
  locals = PyModule_GetDict(module);
  
  while (PyDict_Next(locals, &pos, &key, &value))
  {
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
  
  debug ("python modules loaded");
}



static void
thunarx_python_load_dir (ThunarxProviderPlugin *plugin, const char *dirname)
{
	GDir *dir;
	const char *name;
	gboolean initialized = FALSE;

	debug_enter_args("dirname=%s", dirname);
	
	dir = g_dir_open(dirname, 0, NULL);
	if (!dir)
		return;
			
	while ((name = g_dir_read_name(dir)))
	{
		if (g_str_has_suffix(name, ".py"))
		{
			char *modulename;
			int len;

			len = strlen(name) - 3;
			modulename = g_new0(char, len + 1);
			strncpy(modulename, name, len);

			if (!initialized)
			{
				PyObject *sys_path, *py_path;
				  /* n-p python part is initialized on demand (or not
				   * at all if no extensions are found) */
				if (!thunarx_python_init_python())
				{
					g_warning("thunarx_python_init_python failed");
					g_dir_close(dir);
				}
				  /* sys.path.insert(0, dirname) */
				sys_path = PySys_GetObject("path");
				py_path = PyString_FromString(dirname);
				PyList_Insert(sys_path, 0, py_path);
				Py_DECREF(py_path);
			}

			thunarx_python_load_file(plugin, modulename);
		}
	}
}



G_MODULE_EXPORT void
thunar_extension_initialize (ThunarxProviderPlugin *plugin)
{
  const gchar *mismatch;

  /* verify that the thunarx versions are compatible */
  mismatch = thunarx_check_version (THUNARX_MAJOR_VERSION, THUNARX_MINOR_VERSION, THUNARX_MICRO_VERSION);
  if (G_UNLIKELY (mismatch != NULL))
    {
      g_warning ("Version mismatch: %s", mismatch);
      return;
    }

  debug ("Initializing thunarx-python extension");

  all_types = g_array_new(FALSE, FALSE, sizeof(GType));
  
  thunarx_provider_plugin_set_resident (plugin, TRUE);  
  thunarx_python_load_dir(plugin, THUNARX_EXTENSION_DIR "/python");
}



G_MODULE_EXPORT void
thunar_extension_shutdown (void)
{
  debug ("Shutting down thunarx-python extension");
  
  if (Py_IsInitialized())
    Py_Finalize();
 
  g_array_free (all_types, TRUE);
}



G_MODULE_EXPORT void
thunar_extension_list_types (const GType **types,
                             gint         *n_types)
{
  debug_enter();

  *types = (GType*)all_types->data;
  *n_types = all_types->len;
}

