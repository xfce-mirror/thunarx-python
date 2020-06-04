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
 
#ifndef THUNARX_PYTHON_H
#define THUNARX_PYTHON_H

#include <glib-object.h>
#include <glib/gprintf.h>
#include <Python.h>

#if PY_VERSION_HEX < 0x02050000 && !defined(PY_SSIZE_T_MIN)
typedef int Py_ssize_t;
#define PY_SSIZE_T_MAX INT_MAX
#define PY_SSIZE_T_MIN INT_MIN
#endif

typedef enum {
    THUNARX_PYTHON_DEBUG_ALL = 1 << 0,
} ThunarxPythonDebug;

extern ThunarxPythonDebug thunarx_python_debug;

#define debug(x) { if (thunarx_python_debug & THUNARX_PYTHON_DEBUG_ALL) \
                         g_print("thunarx-python: " x "\n"); }
#define debug_enter()  { if (thunarx_python_debug & THUNARX_PYTHON_DEBUG_ALL) \
                             g_printf("%s: entered\n", __FUNCTION__); }
#define debug_enter_args(x, y) { if (thunarx_python_debug & THUNARX_PYTHON_DEBUG_ALL) \
                                     g_printf("%s: entered " x "\n", __FUNCTION__, y); }

extern PyTypeObject *_PyGtkWidget_Type;
#define PyGtkWidget_Type (*_PyGtkWidget_Type)

extern PyTypeObject *_PyThunarxFileInfo_Type;
#define PyThunarxFileInfo_Type (*_PyThunarxFileInfo_Type)

extern PyTypeObject *_PyThunarxMenuItem_Type;
#define PyThunarxMenuItem_Type (*_PyThunarxMenuItem_Type)

extern PyTypeObject *_PyThunarxMenu_Type;
#define PyThunarxMenu_Type (*_PyThunarxMenu_Type)

extern PyTypeObject *_PyThunarxMenuProvider_Type;
#define PyThunarxMenuProvider_Type (*_PyThunarxMenuProvider_Type)

extern PyTypeObject *_PyThunarxPreferencesProvider_Type;
#define PyThunarxPreferencesProvider_Type (*_PyThunarxPreferencesProvider_Type)

extern PyTypeObject *_PyThunarxPropertyPage_Type;
#define PyThunarxPropertyPage_Type (*_PyThunarxPropertyPage_Type)

extern PyTypeObject *_PyThunarxPropertyPageProvider_Type;
#define PyThunarxPropertyPageProvider_Type (*_PyThunarxPropertyPageProvider_Type)

extern PyTypeObject *_PyThunarxProviderPlugin_Type;
#define PyThunarxProviderPlugin_Type (*_PyThunarxProviderPlugin_Type)

extern PyTypeObject *_PyThunarxRenamer_Type;
#define PyThunarxRenamer_Type (*_PyThunarxRenamer_Type)

extern PyTypeObject *_PyThunarxRenamerProvider_Type;
#define PyThunarxRenamerProvider_Type (*_PyThunarxRenamerProvider_Type)

#endif /* THUNARX_PYTHON_H */
