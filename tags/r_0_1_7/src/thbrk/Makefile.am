# $Id: Makefile.am,v 1.12 2006-09-19 10:48:46 thep Exp $
MAINTAINERCLEANFILES = Makefile.in

dictdatadir = $(datadir)/libthai

INCLUDES = -I. -I$(top_srcdir)/include $(DATRIE_CFLAGS)
DEFS = -DDICT_DIR=\"$(dictdatadir)\"

noinst_LTLIBRARIES = libthbrk.la

libthbrk_la_SOURCES =	\
	thbrk.c		\
	brk-maximal.c	\
	brk-maximal.h

libthbrk_la_LIBADD = $(DATRIE_LIBS)

