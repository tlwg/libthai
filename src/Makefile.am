# $Id: Makefile.am,v 1.9 2001-08-06 14:08:05 thep Exp $
SUBDIRS = thctype thstr thinp thrend thcoll thbrk thwchar thwbrk

MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES = libthai.la

libthai_la_SOURCES = dummy.c
libthai_la_LIBADD = \
	$(top_builddir)/src/thctype/libthctype.la \
	$(top_builddir)/src/thstr/libthstr.la \
	$(top_builddir)/src/thinp/libthinp.la \
	$(top_builddir)/src/thrend/libthrend.la \
	$(top_builddir)/src/thcoll/libthcoll.la \
	$(top_builddir)/src/thbrk/libthbrk.la \
	$(top_builddir)/src/thwchar/libthwchar.la \
	$(top_builddir)/src/thwbrk/libthwbrk.la 

