# $Id: Makefile.am,v 1.7 2001-08-03 11:20:45 thep Exp $
MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = map.c map.h

INCLUDES = -I. -I$(top_srcdir)/include

EXTRA_DIST = tdict.txt

bin_PROGRAMS = cttex
noinst_PROGRAMS = dict2state
noinst_LTLIBRARIES = libthbrk.la

dict2state_SOURCES = dict2state.c

libthbrk_la_SOURCES = map.c map.h thbrk.c

cttex_SOURCES = map.c cttex.c
cttex_LDADD = \
	$(top_builddir)/src/thbrk/libthbrk.la \
	$(top_builddir)/src/thstr/libthstr.la \
	$(top_builddir)/src/thctype/libthctype.la

map.c map.h: tdict.txt dict2state
	$(top_builddir)/src/thbrk/dict2state \
		$(top_srcdir)/src/thbrk/tdict.txt \
		map.c map.h
