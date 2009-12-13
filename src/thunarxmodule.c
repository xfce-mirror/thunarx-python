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
# include "config.h"
#endif

/* include this first, before NO_IMPORT_PYGOBJECT is defined */
#include <pygobject.h>
#include <pygtk/pygtk.h>

void pythunarx_register_classes(PyObject *d);

extern PyMethodDef pythunarx_functions[];

DL_EXPORT(void)
initthunarx(void)
{
    PyObject *m, *d;
    
    if (!g_getenv("INSIDE_THUNARX_PYTHON"))
    {
	    Py_FatalError("This module can only be used from thunarx");
	    return;
    }
	
    if (!pygobject_init(-1, -1, -1))
    {
      PyErr_Print();
      Py_FatalError("Can't initialize module gobject");
    }
    init_pygtk ();

    m = Py_InitModule ("thunarx", pythunarx_functions);
    d = PyModule_GetDict (m);

    pythunarx_register_classes(d);
    
    if (PyErr_Occurred())
    {
      PyErr_Print();
      Py_FatalError("Can't initialize module thunarx");
    }
}
