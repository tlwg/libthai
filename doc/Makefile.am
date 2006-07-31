if ENABLE_DOXYGEN_DOC

pkgdocdir = $(docdir)

all-local:
	$(DOXYGEN)

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

