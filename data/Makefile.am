# $Id: Makefile.am,v 1.6 2008-06-24 14:51:13 thep Exp $
MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = thbrk.br thbrk.tl tdict.txt

dictdatadir = $(datadir)/libthai

if ENABLE_DICT
dictdata_DATA = thbrk.sbm thbrk.br thbrk.tl
else
dictdata_DATA =
endif

TDICT_SRC = 				\
	$(srcdir)/tdict-common.txt	\
	$(srcdir)/tdict-collection.txt	\
	$(srcdir)/tdict-district.txt	\
	$(srcdir)/tdict-geo.txt		\
	$(srcdir)/tdict-ict.txt		\
	$(srcdir)/tdict-science.txt	\
	$(srcdir)/tdict-spell.txt	\
	$(srcdir)/tdict-std.txt		\
	$(srcdir)/tdict-std-compound.txt

EXTRA_DIST = thbrk.sbm $(TDICT_SRC)

tdict.txt: $(TDICT_SRC)
	cat $(TDICT_SRC) | LC_ALL=C sort -u > tdict.txt

thbrk.br thbrk.tl: tdict.txt
	if test ! -e thbrk.sbm; then \
	  ln -s $(top_srcdir)/data/thbrk.sbm . ; \
	fi
	rm -f thbrk.br thbrk.tl
	$(TRIETOOL) thbrk add-list tdict.txt

