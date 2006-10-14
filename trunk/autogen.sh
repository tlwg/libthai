#!/bin/sh

set -x
libtoolize --force
aclocal
automake --add-missing
autoconf

