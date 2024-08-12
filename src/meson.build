ldflags = []
link_depends = ['libthai.map']

if ld_has_version_script
	ldflags += [
		'-Wl,--version-script,@0@'.format(meson.current_source_dir() / 'libthai.map')
	]
else
	ldflags += [
		'-export-symbols @0@'.format(meson.current_source_dir() / 'libthai.map')
	]
endif

thai = library(
	'thai',
	[
		'thctype/thctype.c',
		'thctype/wtt.c',

		'thstr/thstr.c',

		'thcell/thcell.c',

		'thinp/thinp.c',

		'thrend/thrend.c',

		'thcoll/cweight.c',
		'thcoll/cweight.h',
		'thcoll/thcoll.c',

		'thbrk/thbrk.c',
		'thbrk/thbrk-priv.h',
		'thbrk/thbrk-utils.h',
		'thbrk/brk-ctype.c',
		'thbrk/brk-ctype.h',
		'thbrk/brk-common.c',
		'thbrk/brk-common.h',
		'thbrk/brk-maximal.c',
		'thbrk/brk-maximal.h',

		'thwchar/thwchar.c',

		'thwctype/thwctype.c',

		'thwstr/thwstr.c',

		'thwbrk/thwbrk.c',
	],

	install : true,
	link_args : ldflags,
	link_depends : link_depends,
	c_args: ['-DDICT_DIR="@0@"'.format(dict_dir)],
	dependencies : [datrie],
	version : libversion,
	soversion : soversion,
	include_directories : include_dir,
)

pkg = import('pkgconfig')
pkg.generate(
	thai,
	filebase : 'libthai',
	name : 'libthai',
	description : 'Thai support library',
	version : version,
	requires_private: datrie,
)
