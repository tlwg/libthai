# $Id: Makefile.am,v 1.10 2006-08-31 14:50:11 thep Exp $
MAINTAINERCLEANFILES = Makefile.in

INCLUDES = -I. -I$(top_srcdir)/include $(DATRIE_CFLAGS)
DEFS = -DDICT_DIR=\"$(dictdatadir)\"

noinst_LTLIBRARIES = libthbrk.la

libthbrk_la_SOURCES = thbrk.c
libthbrk_la_LIBADD = $(DATRIE_LIBS)

