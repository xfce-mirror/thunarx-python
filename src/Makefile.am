thunar_extensiondir=$(libdir)/thunarx-1

thunar_extension_LTLIBRARIES = libthunarx-python.la

libthunarx_python_la_SOURCES = \
    thunarx_python-object.c                 \
    thunarx_python-object.h                 \
    thunarx_python.c                        \
    thunarx_python.h

libthunarx_python_la_LIBADD = \
    $(PACKAGE_LIBS)         \
    $(PYTHON_LIBS)
 
libthunarx_python_la_LDFLAGS = \
    -module -pthread
    $(PACKAGE_LDFLAGS)
 
libthunarx_python_la_CPPFLAGS = \
    $(PACKAGE_CPPFLAGS)
 
libthunarx_python_la_CFLAGS = \
    $(PACKAGE_CFLAGS)           \
    $(PYTHON_CFLAGS)
 
pyexec_LTLIBRARIES = libthunarx.la
pyexecdir = $(libdir)/thunarx-1/thunarx-python

libthunarx_la_LIBADD = $(PACKAGE_LIBS)
libthunarx_la_SOURCES = thunarxmodule.c
nodist_libthunarx_la_SOURCES = thunarx.c
thunarx.c: thunarx.defs thunarx.override
CLEANFILES = thunarx.c
EXTRA_DIST = thunarx.override thunarx.defs

.defs.c:
	(cd $(srcdir)\
         && $(PYGTK_CODEGEN) \
	    --register $(PYGTK_DEFSDIR)/pango-types.defs \
            --register $(PYGTK_DEFSDIR)/gdk-types.defs \
            --register $(PYGTK_DEFSDIR)/gtk-types.defs \
            --override $*.override \
            --prefix py$* $*.defs) > gen-$*.c \
        && cp gen-$*.c $*.c \
        && rm -f gen-$*.c
