#!/bin/sh

srcdir=${srcdir-.}
top_builddir=${top_builddir-.}

LIBTHAI_DICTDIR=${top_builddir}/data $top_builddir/tests/test_thbrk
