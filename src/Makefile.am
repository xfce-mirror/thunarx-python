
AM_CPPFLAGS =								\
	-I$(top_builddir)						\
	-I$(top_srcdir)							\
	-DG_LOG_DOMAIN=\"thunarx-python\"				\
	-DEXO_API_SUBJECT_TO_CHANGE					\
	-DLIBEXECDIR=\"$(libexecdir)\"					\
	$(PLATFORM_CPPFLAGS)

extensionsdir = $(libdir)/thunarx-2
extensions_LTLIBRARIES =						\
	thunarx-python.la

thunarx_python_la_SOURCES =						\
	txp-provider.c							\
	txp-provider.h							\
	thunarx-python.c

thunarx_python_la_CPPFLAGS =						\
	$(AM_CPPFLAGS)

thunarx_python_la_CFLAGS =						\
	$(PLATFORM_CFLAGS)						\
	$(THUNARX_CFLAGS)						\
	$(EXO_CFLAGS)							\
	$(LIBXFCE4UTIL_CFLAGS)						\
	$(PYTHON_CFLAGS)

thunarx_python_la_LDFLAGS =						\
	-avoid-version							\
	-export-dynamic							\
	-module								\
	$(PLATFORM_LDFLAGS)						\
	$(THUNARX_LDFLAGS)						\
	$(EXO_LDFLAGS)							\
	$(LIBXFCE4UTIL_LDFLAGS)						\
	$(PYTHON_LIBS)

# vi:set ts=8 sw=8 noet ai nocindent:
