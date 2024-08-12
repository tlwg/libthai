ldflags = []
link_depends = ['libthai.map', 'libthai.def']

if ld_has_version_script
    ldflags += [
        '-Wl,--version-script,@0@'.format(
            meson.current_source_dir() / 'libthai.map',
        ),
    ]
else
    ldflags += [
        '-export-symbols @0@'.format(meson.current_source_dir() / 'libthai.def'),
    ]
endif

thai_src = files(
    'thbrk/brk-common.c',
    'thbrk/brk-common.h',
    'thbrk/brk-ctype.c',
    'thbrk/brk-ctype.h',
    'thbrk/brk-maximal.c',
    'thbrk/brk-maximal.h',
    'thbrk/thbrk-priv.h',
    'thbrk/thbrk-utils.h',
    'thbrk/thbrk.c',
    'thcell/thcell.c',
    'thcoll/cweight.c',
    'thcoll/cweight.h',
    'thcoll/thcoll.c',
    'thctype/thctype.c',
    'thctype/wtt.c',
    'thinp/thinp.c',
    'thrend/thrend.c',
    'thstr/thstr.c',
    'thwbrk/thwbrk.c',
    'thwchar/thwchar.c',
    'thwctype/thwctype.c',
    'thwstr/thwstr.c',
)

thai = library(
    'thai',
    thai_src,
    install: true,
    link_args: ldflags,
    link_depends: link_depends,
    c_args: ['-DDICT_DIR="@0@"'.format(dict_dir)],
    dependencies: [datrie],
    version: libversion,
    soversion: soversion,
    include_directories: include_dir,
)
libthai_dep = declare_dependency(
    include_directories: include_dir,
    link_with: thai,
)

pkg = import('pkgconfig')
pkg.generate(
    thai,
    filebase: 'libthai',
    name: 'libthai',
    description: 'Thai support library',
    version: version,
    requires_private: ['datrie-0.2'],
)
