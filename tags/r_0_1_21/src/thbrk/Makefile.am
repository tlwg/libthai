MAINTAINERCLEANFILES = Makefile.in

dictdatadir = $(datadir)/libthai

AM_CPPFLAGS = -I. -I$(top_srcdir)/include $(DATRIE_CFLAGS)
DEFS = -DDICT_DIR=\"$(dictdatadir)\"

noinst_LTLIBRARIES = libthbrk.la

libthbrk_la_SOURCES =	\
	thbrk.c		\
	brk-ctype.c	\
	brk-ctype.h	\
	brk-common.c	\
	brk-common.h	\
	brk-maximal.c	\
	brk-maximal.h	\
	$(NULL)

libthbrk_la_LIBADD = $(DATRIE_LIBS)

