# $Id: Makefile.am,v 1.6 2001-07-27 10:12:23 thep Exp $
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

map.c map.h: tdict.txt dict2state
	$(top_builddir)/src/thbrk/dict2state \
		$(top_srcdir)/src/thbrk/tdict.txt \
		map.c map.h
