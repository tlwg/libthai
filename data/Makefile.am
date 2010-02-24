MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = thbrk.tri tdict.txt

dictdatadir = $(datadir)/libthai

if ENABLE_DICT
dictdata_DATA = thbrk.tri
else
dictdata_DATA =
endif

TDICT_SRC = 				\
	$(srcdir)/tdict-common.txt	\
	$(srcdir)/tdict-collection.txt	\
	$(srcdir)/tdict-district.txt	\
	$(srcdir)/tdict-geo.txt		\
	$(srcdir)/tdict-ict.txt		\
	$(srcdir)/tdict-lang-ethnic.txt	\
	$(srcdir)/tdict-proper.txt	\
	$(srcdir)/tdict-science.txt	\
	$(srcdir)/tdict-spell.txt	\
	$(srcdir)/tdict-std.txt		\
	$(srcdir)/tdict-std-compound.txt

EXTRA_DIST = thbrk.abm $(TDICT_SRC)

tdict.txt: $(TDICT_SRC)
	cat $(TDICT_SRC) | LC_ALL=C sort -u > tdict.txt

thbrk.tri: tdict.txt
	if test ! -e thbrk.abm; then \
	  ln -s $(top_srcdir)/data/thbrk.abm . ; \
	fi
	rm -f thbrk.tri
	$(TRIETOOL) thbrk add-list -e utf-8 tdict.txt

