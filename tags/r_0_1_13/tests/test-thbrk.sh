#!/bin/sh
# $Id: test-thbrk.sh,v 1.1 2006-10-14 10:03:17 thep Exp $

srcdir=${srcdir-.}
top_builddir=${top_builddir-.}

LIBTHAI_DICTDIR=${top_builddir}/data $top_builddir/tests/test_thbrk
