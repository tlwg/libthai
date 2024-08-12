fs = import('fs')

tests = ['thctype', 'thcell', 'thinp', 'thrend', 'thstr', 'thwchar']

foreach item : tests
    exe = executable('test_' + item, 'test_@0@.c'.format(item), link_with: thai)
    test(item, exe)
endforeach

# thcoll
thsort = executable('thsort', 'thsort.c', link_with: thai)
test(
    'thcoll',
    find_program('test-thcoll.sh'),
    depends: [thsort],
    env: {
        'srcdir' : meson.current_source_dir(),
        'top_builddir' : meson.project_build_root(),
    },
)

if get_option('dict')
    foreach item : ['thbrk', 'thwbrk']
        exe = executable(
            'test_' + item,
            'test_@0@.c'.format(item),
            link_with: thai,
        )
        test(
            item,
            exe,
            depends: [tri],
            env: {'LIBTHAI_DICTDIR' : fs.parent(tri.full_path())},
        )
    endforeach
endif
