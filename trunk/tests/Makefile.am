MAINTAINERCLEANFILES = Makefile.in

INCLUDES = -I$(top_srcdir)/include

EXTRA_DIST = sorttest.txt sorted.txt test-thcoll.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir)

TESTS = \
	test-thcoll.sh

check_SCRIPTS = \
	test-thcoll.sh

check_PROGRAMS = \
	thsort

thsort_SOURCES = thsort.c
thsort_LDADD = $(top_builddir)/src/thcoll/libthcoll.la

