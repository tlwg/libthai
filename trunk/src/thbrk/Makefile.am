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

