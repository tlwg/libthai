dict_dir = get_option('datadir') / 'libthai'

if not get_option('dict')
	subdir_done()
endif 

sort = find_program('sort')
cp = find_program('cp')
trietool = find_program('trietool')

dictionary = custom_target(
	'tdict',
	command : [sort, '-u', '-o', '@OUTPUT@', '@INPUT@'],
	env : {
		'LC_ALL': 'C',
	},
	input : [
		'tdict-common.txt',
		'tdict-collection.txt',
		'tdict-currency.txt',
		'tdict-district.txt',
		'tdict-city.txt',
		'tdict-country.txt',
		'tdict-geo.txt',
		'tdict-history.txt',
		'tdict-ict.txt',
		'tdict-lang-ethnic.txt',
		'tdict-proper.txt',
		'tdict-science.txt',
		'tdict-slang.txt',
		'tdict-spell.txt',
		'tdict-std.txt',
		'tdict-std-compound.txt'
	],
	output : ['tdict.txt'],
)
# trietool look for thbrk.abm in the directory of thbrk.tri
# so we need to copy thbrk.abm into the build directory
alphamap = custom_target(
	'alphabet_map',
	command : [cp, '@INPUT@', '@OUTPUT@'],
	input : ['thbrk.abm'],
	output : ['thbrk.abm'],
)
tri = custom_target(
	'tri',
	command : [trietool, 'data/thbrk', 'add-list', '-e', 'utf-8', '@INPUT0@'],
	input : [dictionary],
	depends : [alphamap],
	output : ['thbrk.tri'],
	install : true,
	install_dir: dict_dir,
)
