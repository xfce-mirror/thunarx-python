SUBDIRS = src examples

if ENABLE_GTK_DOC
SUBDIRS += docs
endif

distclean-local:
	rm -rf *.spec *.cache *~

rpm: dist
	rpmbuild -ta $(PACKAGE)-$(VERSION).tar.gz
	@rm -f $(PACKAGE)-$(VERSION).tar.gz

dist-hook:
	echo "==== DIST HOOK ===="
	echo "`pwd`" 
	test -d "$(srcdir)/docs/html" && mv $(srcdir)/docs/html $(distdir)/docs || echo

DISTCHECK_CONFIGURE_FLAGS=--enable-gtk-doc
