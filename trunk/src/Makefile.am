SUBDIRS = thctype thstr thcell thinp thrend thcoll thbrk thwchar thwctype \
	thwstr thwbrk

MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST = libthai.map libthai.def

AM_CPPFLAGS = -I. -I$(top_srcdir)/include $(DATRIE_CFLAGS)

lib_LTLIBRARIES = libthai.la

libthai_sublibs = \
	$(top_builddir)/src/thctype/libthctype.la \
	$(top_builddir)/src/thstr/libthstr.la \
	$(top_builddir)/src/thcell/libthcell.la \
	$(top_builddir)/src/thinp/libthinp.la \
	$(top_builddir)/src/thrend/libthrend.la \
	$(top_builddir)/src/thcoll/libthcoll.la \
	$(top_builddir)/src/thbrk/libthbrk.la \
	$(top_builddir)/src/thwchar/libthwchar.la \
	$(top_builddir)/src/thwctype/libthwctype.la \
	$(top_builddir)/src/thwstr/libthwstr.la \
	$(top_builddir)/src/thwbrk/libthwbrk.la 

if LD_HAS_VERSION_SCRIPT
EXPORTS_FLAGS = -Wl,-version-script -Wl,$(srcdir)/libthai.map
EXPORTS_DEPS = libthai.map
else
EXPORTS_FLAGS = -export-symbols $(srcdir)/libthai.def
EXPORTS_DEPS = libthai.def
endif

libthai_la_SOURCES = libthai.c
libthai_la_LIBADD = $(libthai_sublibs)
libthai_la_LDFLAGS = -no-undefined \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
	$(EXPORTS_FLAGS)
libthai_la_DEPENDENCIES = $(EXPORTS_DEPS) $(libthai_sublibs)

