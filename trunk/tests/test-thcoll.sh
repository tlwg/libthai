#!/bin/sh
# $Id: test-thcoll.sh,v 1.3 2003-09-10 05:29:46 thep Exp $

srcdir=${srcdir-.}
top_builddir=${top_builddir-.}

$top_builddir/tests/thsort $srcdir/sorttest.txt out.txt
cmp $srcdir/sorted.txt out.txt && rm -f out.txt

