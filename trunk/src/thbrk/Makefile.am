# $Id: Makefile.am,v 1.14 2008-12-23 10:16:58 thep Exp $
MAINTAINERCLEANFILES = Makefile.in

dictdatadir = $(datadir)/libthai

INCLUDES = -I. -I$(top_srcdir)/include $(DATRIE_CFLAGS)
DEFS = -DDICT_DIR=\"$(dictdatadir)\"

noinst_LTLIBRARIES = libthbrk.la

libthbrk_la_SOURCES =	\
	thbrk.c		\
	thbrk-private.h	\
	brk-ctype.c	\
	brk-ctype.h	\
	brk-maximal.c	\
	brk-maximal.h

libthbrk_la_LIBADD = $(DATRIE_LIBS)

