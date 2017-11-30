docsdir = $(docdir)

BUILDDIR = $(top_builddir)/docs

REF_VERSION = $(VERSION)
FULL_VERSION = $(VERSION)

XMLFILES = 							\
	reference/thunarx-python-ref.xml			\
	reference/thunarx-python-overview.xml			\
	reference/thunarx-python-overview-example.xml			\
	reference/thunarx-python-class-reference.xml			\
	reference/thunarx-python-provider-reference.xml			\
	reference/thunarx-python-menu-provider.xml \
	reference/thunarx-python-menu-item.xml \
	reference/thunarx-python-menu.xml \
	reference/thunarx-python-property-page.xml \
	reference/thunarx-python-property-page-provider.xml \
	reference/thunarx-python-renamer.xml \
	reference/thunarx-python-renamer-provider.xml \
	reference/thunarx-python-preferences-provider.xml \
	reference/thunarx-python-file-info.xml

HTMLdir = $(HTML_DIR)/thunarx-python
HTML_DATA =						\
	index.html					\
	thunarx-python-overview.html \
	thunarx-python-overview-example.html \
	thunarx-python-class-reference.html \
	thunarx-python-provider-reference.html \
	class-thunarx-python-menu-provider.html  \
	class-thunarx-python-menu-item.html  \
	class-thunarx-python-menu.html  \
	class-thunarx-python-property-page.html  \
	class-thunarx-python-property-page-provider.html  \
	class-thunarx-python-renamer.html  \
	class-thunarx-python-renamer-provider.html  \
	class-thunarx-python-preferences-provider.html  \
	class-thunarx-python-file-info.html  \
	thunarx-python.devhelp2 \
	up.png up-insensitive.png \
	right.png right-insensitive.png \
	left.png left-insensitive.png home.png \
	style.css
	
BUILT_SOURCES = 		\
	reference/builddate.xml \
	$(HTML_DATA)

CLEANFILES = 			\
	thunarx-python-ref.*	\
	reference/builddate.xml \
	$(HTML_DATA)

EXTRA_DIST = 		\
	$(XMLFILES) \
	$(HTML_DATA)

REFERENCE_DEPS = 	\
	reference 	\
	$(XMLFILES)

if ENABLE_GTK_DOC

reference/builddate.xml: $(REFERENCE_DEPS)
	$(PYTHON) -c 'import datetime; print datetime.date.today()' > $@
	
$(HTML_DATA): $(REFERENCE_DEPS) reference/builddate.xml
	$(GTKDOC_MKHTML) thunarx-python reference/thunarx-python-ref.xml
	touch $@
	
endif
