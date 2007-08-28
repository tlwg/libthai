# $Id: Makefile.am,v 1.5 2007-06-18 16:24:56 thep Exp $
MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = thbrk.br thbrk.tl tdict.txt

dictdatadir = $(datadir)/libthai
dictdata_DATA = thbrk.sbm thbrk.br thbrk.tl

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

