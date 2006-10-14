# $Id: Makefile.am,v 1.15 2006-05-04 10:14:27 thep Exp $
SUBDIRS = thctype thstr thcell thinp thrend thcoll thbrk thwchar thwctype \
	thwstr thwbrk

MAINTAINERCLEANFILES = Makefile.in

if OS_WIN32
no_undefined = -no-undefined
else
no_undefined =
endif

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
libthai_la_LDFLAGS = $(no_undefined) \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

