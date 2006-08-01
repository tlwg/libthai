if ENABLE_DOXYGEN_DOC

pkgdocdir = $(docdir)

html.stamp: $(top_srcdir)/include/thai/*.h
	$(DOXYGEN)
	touch html.stamp

all-local: html.stamp

install-data-local:
	$(INSTALL) -d $(DESTDIR)$(pkgdocdir)
	$(INSTALL_DATA) html/* $(DESTDIR)$(pkgdocdir)

uninstall-local:
	rm -rf $(DESTDIR)$(pkgdocdir)

clean-local:
	rm -rf html man

else

install-data-local:
uninstall-local:
clean-local:

endif

