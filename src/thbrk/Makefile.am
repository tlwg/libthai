# $Id: Makefile.am,v 1.8.2.2 2006-08-23 16:31:53 thep Exp $
MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = thbrk.br thbrk.tl

dictdatadir = $(datadir)/libthai
dictdata_DATA = thbrk.sbm thbrk.br thbrk.tl

INCLUDES = -I. -I$(top_srcdir)/include $(DATRIE_CFLAGS)
DEFS = -DDICT_DIR=\"$(dictdatadir)\"

EXTRA_DIST = tdict.txt thbrk.sbm

noinst_LTLIBRARIES = libthbrk.la

libthbrk_la_SOURCES = thbrk.c
libthbrk_la_LIBADD = $(DATRIE_LIBS)

thbrk.br thbrk.tl: tdict.txt
	if test ! -e thbrk.sbm; then \
	  ln -s $(top_srcdir)/src/thbrk/thbrk.sbm . ; \
	fi
	rm -f thbrk.br thbrk.tl
	$(TRIETOOL) thbrk add-list $(top_srcdir)/src/thbrk/tdict.txt

