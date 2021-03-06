# -*- mode: makefile -*-
#
# Makefile.am - template makefile for gtk-doc module
# Copyright (C) 2007-2017  Stefan Sauer
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# As a special exception, the above copyright owner gives unlimited
# permission to copy, distribute and modify this Makefile.am template.
# You need not follow the terms of the GNU General Public License when
# using or distributing such Makefile.am files, even though portions of
# the text of the Makefile.am appear in them. The GNU General Public
# License (GPL) does govern all other use of the material that constitutes
# the Makefile.am template.

# This is a blank Makefile.am for using gtk-doc.
# Copy this to your project's API docs directory and modify the variables to
# suit your project. See the GTK+ Makefiles in gtk+/docs/reference for examples
# of using the various options.

# The name of the module, e.g. 'glib'.
DOC_MODULE=thunarx-python

# Uncomment for versioned docs and specify the version of the module, e.g. '2'.
#DOC_MODULE_VERSION=2

# The top-level XML file.
DOC_MAIN_SGML_FILE=$(DOC_MODULE)-docs.xml

# Directories containing the source code.
# gtk-doc will search all .c and .h files beneath these paths
# for inline comments documenting functions and macros.
# e.g. DOC_SOURCE_DIR=$(top_srcdir)/gtk $(top_srcdir)/gdk
DOC_SOURCE_DIR= 

# Extra options to pass to gtkdoc-scangobj. Normally not needed.
SCANGOBJ_OPTIONS=

# Extra options to supply to gtkdoc-scan.
# e.g. SCAN_OPTIONS=--deprecated-guards="GTK_DISABLE_DEPRECATED"
SCAN_OPTIONS=

# Extra options to supply to gtkdoc-mkdb
# e.g. MKDB_OPTIONS=--xml-mode --output-format=xml
MKDB_OPTIONS=--xml-mode --output-format=xml

# Extra options to supply to gtkdoc-mkhtml
MKHTML_OPTIONS=
#--path $(srcdir)/reference

# Extra options to supply to gtkdoc-fixref. Normally not needed.
# e.g. FIXXREF_OPTIONS=--extra-dir=../gdk-pixbuf/html --extra-dir=../gdk/html
FIXXREF_OPTIONS=

# Used for dependencies. The docs will be rebuilt if any of these change.
# e.g. HFILE_GLOB=$(top_srcdir)/gtk/*.h
# e.g. CFILE_GLOB=$(top_srcdir)/gtk/*.c
HFILE_GLOB=
CFILE_GLOB=

# Extra header to include when scanning, which are not under DOC_SOURCE_DIR
# e.g. EXTRA_HFILES=$(top_srcdir}/contrib/extra.h
EXTRA_HFILES=

# Header files or dirs to ignore when scanning. Use base file/dir names
# e.g. IGNORE_HFILES=gtkdebug.h gtkintl.h private_code
IGNORE_HFILES=

# Images to copy into HTML directory.
# e.g. HTML_IMAGES=$(top_srcdir)/gtk/stock-icons/stock_about_24.png
HTML_IMAGES=

# Extra files that are included by $(DOC_MAIN_SGML_FILE).
# e.g. content_files=running.xml building.xml changes-2.0.xml
content_files=version.xml \
		thunarx-python-overview.xml                   \
		thunarx-python-overview-example.xml                   \
		thunarx-python-class-reference.xml                    \
		thunarx-python-provider-reference.xml                 \
		thunarx-python-menu-provider.xml \
		thunarx-python-menu-item.xml \
		thunarx-python-menu.xml \
		thunarx-python-property-page.xml \
		thunarx-python-property-page-provider.xml \
		thunarx-python-renamer.xml \
		thunarx-python-renamer-provider.xml \
		thunarx-python-preferences-provider.xml \
		thunarx-python-file-info.xml

# Files where gtk-doc abbreviations (#GtkWidget) are expanded
# e.g. expand_content_files=running.xml
expand_content_files=

# CFLAGS and LDFLAGS for compiling gtkdoc-scangobj with your library.
# Only needed if you are using gtkdoc-scangobj to dynamically query widget
# signals and properties.
# e.g. GTKDOC_CFLAGS=-I$(top_srcdir) -I$(top_builddir) $(GTK_DEBUG_FLAGS)
# e.g. GTKDOC_LIBS=$(top_builddir)/gtk/$(gtktargetlib)
GTKDOC_CFLAGS=
GTKDOC_LIBS=

# This includes the standard gtk-doc make rules, copied by gtkdocize.
include $(top_srcdir)/gtk-doc.make

# Other files to distribute
EXTRA_DIST +=                                                           \
		version.xml.in
		thunarx-python-overview.xml                   \
		thunarx-python-overview-example.xml                   \
		thunarx-python-class-reference.xml                    \
		thunarx-python-provider-reference.xml                 \
		thunarx-python-menu-provider.xml \
		thunarx-python-menu-item.xml \
		thunarx-python-menu.xml \
		thunarx-python-property-page.xml \
		thunarx-python-property-page-provider.xml \
		thunarx-python-renamer.xml \
		thunarx-python-renamer-provider.xml \
		thunarx-python-preferences-provider.xml \
		thunarx-python-file-info.xml

-include $(top_srcdir)/git.mk
