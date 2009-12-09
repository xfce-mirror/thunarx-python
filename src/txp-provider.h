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

#ifndef __TXP_PROVIDER_H__
#define __TXP_PROVIDER_H__

#include <thunarx/thunarx.h>

G_BEGIN_DECLS;

typedef struct _TxpProviderClass TxpProviderClass;
typedef struct _TxpProvider      TxpProvider;

#define TXP_TYPE_PROVIDER             (txp_provider_get_type ())
#define TXP_PROVIDER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), TXP_TYPE_PROVIDER, TxpProvider))
#define TXP_PROVIDER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), TXP_TYPE_PROVIDER, TxpProviderClass))
#define TXP_IS_PROVIDER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TXP_TYPE_PROVIDER))
#define TXP_IS_PROVIDER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), TXP_TYPE_PROVIDER))
#define TXP_PROVIDER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), TXP_TYPE_PROVIDER, TxpProviderClass))

GType txp_provider_get_type      (void) G_GNUC_CONST G_GNUC_INTERNAL;
void  txp_provider_register_type (ThunarxProviderPlugin *plugin) G_GNUC_INTERNAL;

G_END_DECLS;

#endif /* !__TXP_PROVIDER_H__ */
