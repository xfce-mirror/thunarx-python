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

#include <exo/exo.h>

#include <txp-provider.h>



static GType type_list[1];



/* delcare it here to make the compiler happy */
G_MODULE_EXPORT void thunar_extension_initialize (ThunarxProviderPlugin *plugin);

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

#ifdef G_ENABLE_DEBUG
  g_message ("Initializing thunar-vcs-plugin extension");
#endif

  /* register the types provided by this plugin */
  txp_provider_register_type (plugin);

  /* setup the plugin provider type list */
  type_list[0] = TXP_TYPE_PROVIDER;
}



/* delcare it here to make the compiler happy */
G_MODULE_EXPORT void thunar_extension_shutdown (void);

G_MODULE_EXPORT void
thunar_extension_shutdown (void)
{
#ifdef G_ENABLE_DEBUG
  g_message ("Shutting down thunar-vcs-plugin extension");
#endif
}



/* delcare it here to make the compiler happy */
G_MODULE_EXPORT void thunar_extension_list_types (const GType **types, gint *n_types);

G_MODULE_EXPORT void
thunar_extension_list_types (const GType **types,
                             gint         *n_types)
{
  *types = type_list;
  *n_types = G_N_ELEMENTS (type_list);
}

