# $Id: Makefile.am,v 1.7 2001-08-03 10:51:51 thep Exp $
SUBDIRS = thctype thstr thcoll thbrk thwchar thwbrk

MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES = libthai.la

libthai_la_SOURCES = dummy.c
libthai_la_LIBADD = \
	$(top_builddir)/src/thctype/libthctype.la \
	$(top_builddir)/src/thstr/libthstr.la \
	$(top_builddir)/src/thcoll/libthcoll.la \
	$(top_builddir)/src/thbrk/libthbrk.la \
	$(top_builddir)/src/thwchar/libthwchar.la \
	$(top_builddir)/src/thwbrk/libthwbrk.la 

