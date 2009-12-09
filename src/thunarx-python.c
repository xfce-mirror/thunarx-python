/*-
 * Copyright (c) 2006 Peter de Ridder <peter@xfce.org>
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

#include <exo/exo.h>

#include <txp-provider.h>

#define DEBUG_ENABLED 1
#define debug(x) { if (DEBUG_ENABLED) g_print("thunarx-python: " x "\n"); }

static GType type_list[1];

/* delcare it here to make the compiler happy */
G_MODULE_EXPORT void thunar_extension_initialize (ThunarxProviderPlugin *plugin);

static gboolean thunarx_python_init_python (void);


static gboolean 
thunarx_python_init_python (void)
{
  GModule *libpython;
  char *argv[] = { "thunarx", NULL };
  
  debug("thunarx_python_init_python");

  if (Py_IsInitialized())
    return TRUE;

  debug ("g_module_open libpython");  
  libpython = g_module_open ("/usr/lib/libpython2.6.so", 0);
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
  
  return TRUE;
}



static void
thunarx_python_load_dir (const gchar *dirname)
{
  if (thunarx_python_init_python())
  {
    debug ("python loaded");
  }
  else
  {
    debug ("python not loaded");
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

  /* register the types provided by this plugin */
  txp_provider_register_type (plugin);

  /* setup the plugin provider type list */
  type_list[0] = TXP_TYPE_PROVIDER;
  
  thunarx_python_load_dir("/home/adam/Development/xfce/thunarx-python-modules");
}



/* delcare it here to make the compiler happy */
G_MODULE_EXPORT void thunar_extension_shutdown (void);

G_MODULE_EXPORT void
thunar_extension_shutdown (void)
{
  debug ("Shutting down thunarx-python extension");
  
  if (Py_IsInitialized())
    Py_Finalize();
}



/* declare it here to make the compiler happy */
G_MODULE_EXPORT void thunar_extension_list_types (const GType **types, gint *n_types);

G_MODULE_EXPORT void
thunar_extension_list_types (const GType **types,
                             gint         *n_types)
{
  *types = type_list;
  *n_types = G_N_ELEMENTS (type_list);
}

