# $Id: Makefile.am,v 1.5 2001-07-27 10:43:07 thep Exp $
SUBDIRS = thctype thcoll thbrk thwchar

MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES = libthai.la

libthai_la_SOURCES = dummy.c
libthai_la_LIBADD = \
	$(top_builddir)/src/thctype/libthctype.la \
	$(top_builddir)/src/thcoll/libthcoll.la \
	$(top_builddir)/src/thbrk/libthbrk.la \
	$(top_builddir)/src/thwchar/libthwchar.la

