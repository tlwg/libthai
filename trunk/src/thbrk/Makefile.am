# $Id: Makefile.am,v 1.11 2006-09-01 02:08:04 thep Exp $
MAINTAINERCLEANFILES = Makefile.in

dictdatadir = $(datadir)/libthai

INCLUDES = -I. -I$(top_srcdir)/include $(DATRIE_CFLAGS)
DEFS = -DDICT_DIR=\"$(dictdatadir)\"

noinst_LTLIBRARIES = libthbrk.la

libthbrk_la_SOURCES = thbrk.c
libthbrk_la_LIBADD = $(DATRIE_LIBS)

