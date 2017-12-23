AM_CPPFLAGS =								\
	-I$(top_builddir)						\
	-I$(top_srcdir)							\
	-DDATADIR=\"$(datadir)\"					\
	-DG_LOG_DOMAIN=\"thunarx-python\"				\
	-DEXO_API_SUBJECT_TO_CHANGE					\
	-DLIBEXECDIR=\"$(libexecdir)\"					\
	-DPY_LIB_LOC=\"$(PYTHON_LIB_LOC)\"				\
	-DPYTHON_LIB_NAME=\"$(PYTHON_LIB_NAME)\"				\
	-DTHUNARX_API_VERSION=$(THUNARX_API_VERSION) \
	-DGI_TYPELIB_PATH=\"$(libdir)/girepository-1.0\"


extensionsdir = $(THUNARX_LIBDIR)/thunarx-$(THUNARX_API_VERSION)
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
	$(PYTHON_INCLUDES)						\
	$(PYGOBJECT_CFLAGS)							

thunarx_python_la_LDFLAGS =						\
	-avoid-version							\
	-module								\
	$(THUNARX_LDFLAGS)						\
	$(PYTHON_LDFLAGS)						\
	$(PYGOBJECT_CFLAGS)						

thunarx_python_la_LIBADD =						\
	$(THUNARX_LIBS)						\
	$(PYTHON_LIBS)						\
	$(PYGOBJECT_LIBS)						
