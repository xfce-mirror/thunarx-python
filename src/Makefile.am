thunar_extensiondir=$(libdir)/thunarx-1

thunar_extension_LTLIBRARIES = thunarx-python.la

thunarx_python_la_SOURCES = \
    thunarx_python-object.c                 \
    thunarx_python-object.h                 \
    thunarx_python.c                        \
    thunarx_python.h

thunarx_python_la_LIBADD = \
    $(PACKAGE_LIBS)
 
thunarx_python_la_LDFLAGS = \
    -module -pthread
    $(PACKAGE_LDFLAGS)
 
thunarx_python_la_CPPFLAGS = \
    $(PACKAGE_CPPFLAGS)
 
thunarx_python_la_CFLAGS = \
    $(PACKAGE_CFLAGS)
 
pyexec_LTLIBRARIES = thunarx.la
pyexecdir = $(libdir)/thunarx-1/thunarx-python

thunarx_la_LIBADD = $(PACKAGE_LIBS)
thunarx_la_SOURCES = thunarxmodule.c
nodist_thunarx_la_SOURCES = thunarx.c
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
