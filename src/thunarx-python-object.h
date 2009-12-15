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

#ifndef THUNARX_PYTHON_OBJECT_H
#define THUNARX_PYTHON_OBJECT_H

#include <Python.h>
#include <glib-object.h>

#include <thunarx/thunarx.h>

G_BEGIN_DECLS

typedef struct _ThunarxPythonObject       ThunarxPythonObject;
typedef struct _ThunarxPythonObjectClass  ThunarxPythonObjectClass;

struct _ThunarxPythonObject {
  GObject parent_slot;
  PyObject *instance;
};

struct _ThunarxPythonObjectClass {
  GObjectClass parent_slot;
  PyObject *type;
};

static void
thunarx_python_object_menu_provider_iface_init (ThunarxMenuProviderIface *iface);
static GList *
thunarx_python_object_get_file_actions (ThunarxMenuProvider *provider,
                                        GtkWidget *window,
                                        GList *files);
static GList *
thunarx_python_object_get_folder_actions (ThunarxMenuProvider *provider,
 		  									                  GtkWidget *window,
	  										                  ThunarxFileInfo *folder);
static GList *
thunarx_python_object_get_dnd_actions (ThunarxMenuProvider *provider,
 		  									                  GtkWidget *window,
	  										                  ThunarxFileInfo *folder,
	  										                  GList *files);

static void 
thunarx_python_object_instance_init (ThunarxPythonObject *object);
static void
thunarx_python_object_finalize (GObject *object);
static void
thunarx_python_object_class_init (ThunarxPythonObjectClass *klass,
								                  gpointer class_data);

GType 
thunarx_python_object_get_type (ThunarxProviderPlugin *plugin, PyObject *type);

G_END_DECLS

#endif
