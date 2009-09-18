/*
 *  thunarx-python.c - Thunarx Python extension
 * 
 *  Copyright (C) 2004 Johan Dahlin
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
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
    THUNARX_PYTHON_DEBUG_MISC = 1 << 0,
} ThunarxPythonDebug;

extern ThunarxPythonDebug thunarx_python_debug;

#define debug(x) { if (thunarx_python_debug & THUNARX_PYTHON_DEBUG_MISC) \
                       g_printf( "thunarx-python:" x "\n"); }
#define debug_enter()  { if (thunarx_python_debug & THUNARX_PYTHON_DEBUG_MISC) \
                             g_printf("%s: entered\n", __FUNCTION__); }
#define debug_enter_args(x, y) { if (thunarx_python_debug & THUNARX_PYTHON_DEBUG_MISC) \
                                     g_printf("%s: entered " x "\n", __FUNCTION__, y); }


PyTypeObject *_PyGtkWidget_Type;
#define PyGtkWidget_Type (*_PyGtkWidget_Type)

PyTypeObject *_PyThunarxInfoProvider_Type;
#define PyThunarxInfoProvider_Type (*_PyThunarxInfoProvider_Type)

PyTypeObject *_PyThunarxLocationWidgetProvider_Type;
#define PyThunarxLocationWidgetProvider_Type (*_PyThunarxLocationWidgetProvider_Type)

PyTypeObject *_PyThunarxMenu_Type;
#define PyThunarxMenu_Type (*_PyThunarxMenu_Type)

PyTypeObject *_PyThunarxMenuItem_Type;
#define PyThunarxMenuItem_Type (*_PyThunarxMenuItem_Type)

PyTypeObject *_PyThunarxMenuProvider_Type;
#define PyThunarxMenuProvider_Type (*_PyThunarxMenuProvider_Type)

PyTypeObject *_PyThunarxPropertyPage_Type;
#define PyThunarxPropertyPage_Type (*_PyThunarxPropertyPage_Type)

PyTypeObject *_PyThunarxPropertyPageProvider_Type;
#define PyThunarxPropertyPageProvider_Type (*_PyThunarxPropertyPageProvider_Type)

#endif /* THUNARX_PYTHON_H */
