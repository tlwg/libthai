ACLOCAL_AMFLAGS = -I m4

SUBDIRS = include src data tests doc win32

EXTRA_DIST = \
	build-aux/git-version-gen	\
	$(NULL)

MAINTAINERCLEANFILES = Makefile.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libthai.pc

dist-hook:
	echo $(VERSION) > $(distdir)/VERSION
