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

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <libxfce4util/libxfce4util.h>

#include <thunarx-python/txp-provider.h>


static void   txp_provider_menu_provider_init   (ThunarxMenuProviderIface *iface);
static void   txp_provider_finalize             (GObject                  *object);
static GList *txp_provider_get_file_actions     (ThunarxMenuProvider      *menu_provider,
                                                 GtkWidget                *window,
                                                 GList                    *files);
static GList *txp_provider_get_folder_actions   (ThunarxMenuProvider      *menu_provider,
                                                 GtkWidget                *window,
                                                 ThunarxFileInfo          *folder);



struct _TxpProviderClass
{
  GObjectClass __parent__;
};

struct _TxpProvider
{
  GObject __parent__;

  gchar          *child_watch_path;
  gint            child_watch_id;
};



THUNARX_DEFINE_TYPE_WITH_CODE (TxpProvider,
                               txp_provider,
                               G_TYPE_OBJECT,
                               THUNARX_IMPLEMENT_INTERFACE (THUNARX_TYPE_MENU_PROVIDER,
                                                            txp_provider_menu_provider_init));


static void
txp_provider_class_init (TxpProviderClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = txp_provider_finalize;
}



static void
txp_provider_menu_provider_init (ThunarxMenuProviderIface *iface)
{
  iface->get_file_actions = txp_provider_get_file_actions;
  iface->get_folder_actions = txp_provider_get_folder_actions;
}


static void
txp_provider_init (TxpProvider *txp_provider)
{
}



static void
txp_provider_finalize (GObject *object)
{
  (*G_OBJECT_CLASS (txp_provider_parent_class)->finalize) (object);
}



static GList*
txp_provider_get_file_actions (ThunarxMenuProvider *menu_provider,
                               GtkWidget           *window,
                               GList               *files)
{
  GList              *actions = NULL;
  GtkWidget          *action = NULL;
  
  action = g_object_new (GTK_TYPE_ACTION,
                         "name", "Txp::testitem1",
                         "icon-name", NULL,
                         "label", "TEST ITEM 1",
                         NULL);
  g_signal_connect (action, "activate", NULL, NULL);

  actions = g_list_append (actions, action);

  return actions;
}



static GList*
txp_provider_get_folder_actions (ThunarxMenuProvider *menu_provider,
                                 GtkWidget           *window,
                                 ThunarxFileInfo     *folder)
{
  GList              *actions = NULL;
  return actions;
}
