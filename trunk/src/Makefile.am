# $Id: Makefile.am,v 1.4 2001-07-16 10:54:04 thep Exp $
SUBDIRS = thctype thcoll thbrk

MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES = libthai.la

libthai_la_SOURCES = dummy.c
libthai_la_LIBADD = \
	$(top_builddir)/src/thctype/libthctype.la \
	$(top_builddir)/src/thcoll/libthcoll.la \
	$(top_builddir)/src/thbrk/libthbrk.la

