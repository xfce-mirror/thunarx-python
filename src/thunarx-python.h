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

#define DEBUG_ENABLED 1
#define debug(x) { if (DEBUG_ENABLED) g_print("thunarx-python: " x "\n"); }
#define debug_enter()  { if (DEBUG_ENABLED) \
                             g_printf("%s: entered\n", __FUNCTION__); }
#define debug_enter_args(x, y) { if (DEBUG_ENABLED) \
                                     g_printf("%s: entered " x "\n", __FUNCTION__, y); }

PyTypeObject *_PyGtkWidget_Type;
#define PyGtkWidget_Type (*_PyGtkWidget_Type)

PyTypeObject *_PyGtkAction_Type;
#define PyGtkAction_Type (*_PyGtkAction_Type)

PyTypeObject *_PyThunarxFileInfo_Type;
#define PyThunarxFileInfo_Type (*_PyThunarxFileInfo_Type)

PyTypeObject *_PyThunarxMenuProvider_Type;
#define PyThunarxMenuProvider_Type (*_PyThunarxMenuProvider_Type)

PyTypeObject *_PyThunarxPreferencesProvider_Type;
#define PyThunarxPreferencesProvider_Type (*_PyThunarxPreferencesProvider_Type)

PyTypeObject *_PyThunarxPropertyPage_Type;
#define PyThunarxPropertyPage_Type (*_PyThunarxPropertyPage_Type)

PyTypeObject *_PyThunarxPropertyPageProvider_Type;
#define PyThunarxPropertyPageProvider_Type (*_PyThunarxPropertyPageProvider_Type)

PyTypeObject *_PyThunarxProviderPlugin_Type;
#define PyThunarxProviderPlugin_Type (*_PyThunarxProviderPlugin_Type)

PyTypeObject *_PyThunarxRenamer_Type;
#define PyThunarxRenamer_Type (*_PyThunarxRenamer_Type)

PyTypeObject *_PyThunarxRenamerProvider_Type;
#define PyThunarxRenamerProvider_Type (*_PyThunarxRenamerProvider_Type)

#endif /* THUNARX_PYTHON_H */
