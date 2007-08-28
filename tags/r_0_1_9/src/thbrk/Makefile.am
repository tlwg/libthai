# $Id: Makefile.am,v 1.13 2007-06-11 05:13:55 thep Exp $
MAINTAINERCLEANFILES = Makefile.in

dictdatadir = $(datadir)/libthai

INCLUDES = -I. -I$(top_srcdir)/include $(DATRIE_CFLAGS)
DEFS = -DDICT_DIR=\"$(dictdatadir)\"

noinst_LTLIBRARIES = libthbrk.la

libthbrk_la_SOURCES =	\
	thbrk.c		\
	brk-ctype.c	\
	brk-ctype.h	\
	brk-maximal.c	\
	brk-maximal.h

libthbrk_la_LIBADD = $(DATRIE_LIBS)

