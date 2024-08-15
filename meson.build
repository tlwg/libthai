project(
    'libthai',
    'c',
    meson_version: '>=1.0.0',
    version: run_command(files('build-aux/git-version-gen'), check: true).stdout().strip(),
)

sh = find_program('sh')
compiler = meson.get_compiler('c')
datrie = dependency('datrie-0.2')

version = run_command(files('build-aux/git-version-gen'), check: true).stdout().strip()
meson.add_dist_script(
    sh,
    '-c',
    'echo "@0@" > "$MESON_DIST_ROOT/VERSION"'.format(version),
)
meson.add_dist_script(sh, '-c', 'cd "$MESON_DIST_ROOT" && ./autogen.sh')
meson.add_dist_script(
    sh,
    '-c',
    'cd "$MESON_DIST_ROOT" && rm -r autom4te.cache autogen.sh || true',
)

LT_CURRENT = 3
LT_REVISION = 1
LT_AGE = 3

soversion = LT_CURRENT - LT_AGE
libversion = '@0@.@1@.@2@'.format(soversion, LT_AGE, LT_REVISION)

# Detect for version-script support
ld_has_version_script = compiler.has_link_argument(
    '-Wl,-version-script,@0@'.format(
        meson.global_source_root() / 'build-aux' / 'test.map',
    ),
)

if get_option('buildtype') in ['debug', 'debugoptimized']
    add_project_arguments('-DNDEBUG', language: ['c'])
endif

subdir('data')
subdir('include')
subdir('src')
subdir('man')
subdir('doc')
subdir('tests')
