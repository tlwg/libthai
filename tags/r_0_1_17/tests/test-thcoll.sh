#!/bin/sh

srcdir=${srcdir-.}
top_builddir=${top_builddir-.}

$top_builddir/tests/thsort $srcdir/sorttest.txt out.txt
cmp $srcdir/sorted.txt out.txt && rm -f out.txt

