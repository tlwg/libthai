# $Id: Makefile.am,v 1.2 2001-07-17 03:55:00 thep Exp $
MAINTAINERCLEANFILES = Makefile.in

INCLUDES = -I. -I$(top_srcdir)/include

EXTRA_DIST = tdict.txt

bin_PROGRAMS = cttex
noinst_PROGRAMS = dict2state
noinst_LTLIBRARIES = libthbrk.la

TESTS = test_thbrk
check_PROGRAMS = test_thbrk

dict2state_SOURCES = dict2state.c

libthbrk_la_SOURCES = map.c map.h thbrk.c

cttex_SOURCES = map.c cttex.c

test_thbrk_SOURCES = test_thbrk.c
test_thbrk_LDADD = libthbrk.la

map.h: tdict.txt dict2state
	$(top_builddir)/src/thbrk/dict2state \
		$(top_srcdir)/src/thbrk/tdict.txt \
		$(top_srcdir)/src/thbrk/map.c \
		$(top_srcdir)/src/thbrk/map.h

map.c: tdict.txt dict2state
	$(top_builddir)/src/thbrk/dict2state \
		$(top_srcdir)/src/thbrk/tdict.txt \
		$(top_srcdir)/src/thbrk/map.c \
		$(top_srcdir)/src/thbrk/map.h

