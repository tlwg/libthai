# $Id: Makefile.am,v 1.7 2001-08-03 11:20:45 thep Exp $
MAINTAINERCLEANFILES = Makefile.in

INCLUDES = -I$(top_srcdir)/include

EXTRA_DIST = sorttest.txt sorted.txt test-thcoll.sh

TESTS_ENVIRONMENT = top_builddir=$(top_builddir)

TESTS = \
	test_thctype \
	test_thstr \
	test-thcoll.sh \
	test_thbrk \
	test_thwchar \
	test_thwbrk

check_SCRIPTS = \
	test-thcoll.sh

check_PROGRAMS = \
	test_thctype \
	test_thstr \
	thsort \
	test_thbrk \
	test_thwchar \
	test_thwbrk

test_thctype_SOURCES = test_thctype.c
test_thctype_LDADD = $(top_builddir)/src/thctype/libthctype.la

test_thstr_SOURCES = test_thstr.c
test_thstr_LDADD = \
	$(top_builddir)/src/thstr/libthstr.la \
	$(top_builddir)/src/thctype/libthctype.la

thsort_SOURCES = thsort.c
thsort_LDADD = \
	$(top_builddir)/src/thcoll/libthcoll.la \
	$(top_builddir)/src/thctype/libthctype.la

test_thbrk_SOURCES = test_thbrk.c
test_thbrk_LDADD = \
	$(top_builddir)/src/thbrk/libthbrk.la \
	$(top_builddir)/src/thstr/libthstr.la \
	$(top_builddir)/src/thctype/libthctype.la

test_thwchar_SOURCES = test_thwchar.c
test_thwchar_LDADD = $(top_builddir)/src/thwchar/libthwchar.la

test_thwbrk_SOURCES = test_thwbrk.c
test_thwbrk_LDADD = \
 	$(top_builddir)/src/thwbrk/libthwbrk.la \
	$(top_builddir)/src/thwchar/libthwchar.la \
	$(top_builddir)/src/thbrk/libthbrk.la \
	$(top_builddir)/src/thstr/libthstr.la \
	$(top_builddir)/src/thctype/libthctype.la

