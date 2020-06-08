ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

SUBDIRS = src examples

if ENABLE_GTK_DOC
SUBDIRS += docs
CLEANFILES = html.stamp
endif

DISTCHECK_CONFIGURE_FLAGS=--enable-gtk-doc
