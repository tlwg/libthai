# $Id: Makefile.am,v 1.3 2001-07-27 10:12:24 thep Exp $
MAINTAINERCLEANFILES = Makefile.in

INCLUDES = -I$(top_srcdir)/include

EXTRA_DIST = sorttest.txt sorted.txt test-thcoll.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir)

TESTS = \
	test-thcoll.sh \
	test_thbrk

check_SCRIPTS = \
	test-thcoll.sh

check_PROGRAMS = \
	thsort \
	test_thbrk

thsort_SOURCES = thsort.c
thsort_LDADD = $(top_builddir)/src/thcoll/libthcoll.la

test_thbrk_SOURCES = test_thbrk.c
test_thbrk_LDADD = $(top_builddir)/src/thbrk/libthbrk.la

