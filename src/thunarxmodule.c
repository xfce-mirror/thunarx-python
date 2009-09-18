/* -*- Mode: C; c-basic-offset: 4 -*-
 * Copyright (C) 2004  Johan Dahlin
 *
 *   thunarx.override: overrides for the thunarx extension library
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */


#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/* include this first, before NO_IMPORT_PYGOBJECT is defined */
#include <pygobject.h>
#include <pygtk/pygtk.h>
#include "pygnomevfs.h"

void pythunarx_register_classes (PyObject *d);
void pythunarx_add_constants(PyObject *module, const gchar *strip_prefix);

extern PyMethodDef pythunarx_functions[];

DL_EXPORT(void)
initthunarx(void)
{
    PyObject *m, *d;
    
    if (!g_getenv("INSIDE_NAUTILUS_PYTHON")) {
	Py_FatalError("This module can only be used from thunarx");
	return;
    }
	
    init_pygobject ();
    init_pygtk ();
    init_pygnomevfs();

    m = Py_InitModule ("thunarx", pythunarx_functions);
    d = PyModule_GetDict (m);
	
    pythunarx_register_classes (d);
    pythunarx_add_constants(m, "NAUTILUS_");    
}
