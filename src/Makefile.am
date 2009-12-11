
AM_CPPFLAGS =								\
	-I$(top_builddir)						\
	-I$(top_srcdir)							\
	-DG_LOG_DOMAIN=\"thunarx-python\"				\
	-DEXO_API_SUBJECT_TO_CHANGE					\
	-DLIBEXECDIR=\"$(libexecdir)\"

extensionsdir = $(libdir)/thunarx-2
extensions_LTLIBRARIES =						\
	thunarx-python.la

thunarx_python_la_SOURCES =						\
	thunarx-python.c						\
	thunarx-python.h						\
	thunarx-python-object.c						\
	thunarx-python-object.h

thunarx_python_la_CFLAGS =						\
	$(THUNARX_CFLAGS)						\
	$(PYTHON_CFLAGS)						\
	$(PYGTK_CFLAGS)							\
	$(GNOMEPYTHON_CFLAGS)

thunarx_python_la_LDFLAGS =						\
	-avoid-version							\
	-export-dynamic							\
	-module								\
	$(THUNARX_LDFLAGS)						\
	$(PYTHON_LDFLAGS)						\
	$(PYGTK_LDFLAGS)						\
	$(GNOMEPYTHON_LIBS)

pyexec_LTLIBRARIES = thunarx.la
pyexecdir = $(THUNARX_LIBDIR)/thunarx-python

thunarx_la_LDFLAGS =							\
	-module								\
	-avoid-version							\
	-export-symbols-regex						\
	initthunarx							\
	$(THUNARX_LDFLAGS)						\
	$(PYTHON_LDFLAGS)						\
	$(PYGTK_LDFLAGS)						\
	$(GNOMEPYTHON_LDFLAGS)

thunarx_la_LIBADD =							\
	$(THUNARX_LIBS)							\
	$(PYTHON_LIBS)							\
	$(GNOMEPYTHON_LIBS)						\
	$(PYGTK_LIBS)

thunarx_la_CFLAGS =							\
	$(THUNARX_CFLAGS)						\
	$(PYTHON_CFLAGS)						\
	$(PYGTK_CFLAGS)							\
	$(GNOMEPYTHON_CFLAGS)

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

# vi:set ts=8 sw=8 noet ai nocindent:
