# $Id: Makefile.am,v 1.3 2001-06-13 15:35:21 thep Exp $
SUBDIRS = thctype thcoll

MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES = libthai.la

libthai_la_SOURCES = dummy.c
libthai_la_LIBADD = \
	$(top_builddir)/src/thctype/libthctype.la \
	$(top_builddir)/src/thcoll/libthcoll.la

