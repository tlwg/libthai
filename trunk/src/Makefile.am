# $Id: Makefile.am,v 1.13 2001-09-30 14:03:25 thep Exp $
SUBDIRS = thctype thstr thcell thinp thrend thcoll thbrk thwchar thwctype \
	thwstr thwbrk

MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES = libthai.la

libthai_la_SOURCES = dummy.c
libthai_la_LIBADD = \
	$(top_builddir)/src/thctype/libthctype.la \
	$(top_builddir)/src/thstr/libthstr.la \
	$(top_builddir)/src/thcell/libthcell.la \
	$(top_builddir)/src/thinp/libthinp.la \
	$(top_builddir)/src/thrend/libthrend.la \
	$(top_builddir)/src/thcoll/libthcoll.la \
	$(top_builddir)/src/thbrk/libthbrk.la \
	$(top_builddir)/src/thwchar/libthwchar.la \
	$(top_builddir)/src/thwctype/libthwctype.la \
	$(top_builddir)/src/thwstr/libthwstr.la \
	$(top_builddir)/src/thwbrk/libthwbrk.la 

