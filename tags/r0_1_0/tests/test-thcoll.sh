#!/bin/sh
# $Id: test-thcoll.sh,v 1.2 2001-06-12 13:14:23 thep Exp $

srcdir=${srcdir-.}
top_builddir=${top_builddir-.}

$top_builddir/tests/thsort $srcdir/sorttest.txt out.txt
cmp $srcdir/sorted.txt out.txt

