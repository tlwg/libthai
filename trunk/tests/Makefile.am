# $Id: Makefile.am,v 1.4 2001-07-30 11:41:43 ott Exp $
MAINTAINERCLEANFILES = Makefile.in

INCLUDES = -I$(top_srcdir)/include

EXTRA_DIST = sorttest.txt sorted.txt test-thcoll.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir)

TESTS = \
	test-thcoll.sh \
	test_thbrk \
	test_thwchar \
	test_thwbrk

check_SCRIPTS = \
	test-thcoll.sh

check_PROGRAMS = \
	thsort \
	test_thbrk \
	test_thwchar \
	test_thwbrk

thsort_SOURCES = thsort.c
thsort_LDADD = $(top_builddir)/src/thcoll/libthcoll.la

test_thbrk_SOURCES = test_thbrk.c
test_thbrk_LDADD = $(top_builddir)/src/thbrk/libthbrk.la

test_thwchar_SOURCES = test_thwchar.c
test_thwchar_LDADD = $(top_builddir)/src/thwchar/libthwchar.la

test_thwbrk_SOURCES = test_thwbrk.c
test_thwbrk_LDADD = 	$(top_builddir)/src/thwbrk/libthwbrk.la \
			$(top_builddir)/src/thwchar/libthwchar.la \
			$(top_builddir)/src/thbrk/libthbrk.la 

