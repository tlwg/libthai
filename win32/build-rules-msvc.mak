# NMake Makefile portion for compilation rules
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.  The format
# of NMake Makefiles here are different from the GNU
# Makefiles.  Please see the comments about these formats.

# Inference rules for compiling the .obj files.
# Used for libs and programs with more than a single source file.
# Format is as follows
# (all dirs must have a trailing '\'):
#
# {$(srcdir)}.$(srcext){$(destdir)}.obj::
# 	$(CC)|$(CXX) $(cflags) /Fo$(destdir) /c @<<
# $<
# <<
{..\src\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thbrk\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thcell\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thcoll\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thctype\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thinp\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thrend\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thstr\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thwbrk\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thwchar\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thwctype\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\src\thwstr\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\}.obj::
	$(CC) $(CFLAGS) $(LIBTHAI_BASE_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ /c @<<
$<
<<

{..\tests\}.c{vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\}.obj::
	@if not exist vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\ $(MAKE) /f Makefile.vc CFG=$(CFG) vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests
	$(CC) $(CFLAGS) $(LIBTHAI_TEST_CFLAGS) /Fovs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\ /Fdvs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\ /c @<<
$<
<<

vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\brk-common-test.obj: ..\src\thbrk\brk-common.c
	@if not exist vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\ $(MAKE) /f Makefile.vc CFG=$(CFG) vs$(PDBVER)\$(CFG)\$(PLAT)\libthai
	$(CC) $(CFLAGS) $(LIBTHAI_TEST_CFLAGS) /Fo$@ /Fd$(@D)\ $** /c

# Rules for building .lib files
vs$(PDBVER)\$(CFG)\$(PLAT)\thai.lib: vs$(PDBVER)\$(CFG)\$(PLAT)\thai.dll

# Rules for linking DLLs
# Format is as follows (the mt command is needed for MSVC 2005/2008 builds):
# $(dll_name_with_path): $(dependent_libs_files_objects_and_items)
#	link /DLL [$(linker_flags)] [$(dependent_libs)] [/def:$(def_file_if_used)] [/implib:$(lib_name_if_needed)] -out:$@ @<<
# $(dependent_objects)
# <<
# 	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2
vs$(PDBVER)\$(CFG)\$(PLAT)\thai.dll:		\
vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\thai.def	\
vs$(PDBVER)\$(CFG)\$(PLAT)\libthai.pc	\
$(libthai_dll_OBJS)
	link /DLL $(LDFLAGS) /implib:$(@R).lib /def:vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\thai.def	\
	$(LIBTHAI_DEP_LIBS) -out:$@ @<<
$(libthai_dll_OBJS)
<<
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;2

# Rules for linking Executables
# Format is as follows (the mt command is needed for MSVC 2005/2008 builds):
# $(dll_name_with_path): $(dependent_libs_files_objects_and_items)
#	link [$(linker_flags)] [$(dependent_libs)] -out:$@ @<<
# $(dependent_objects)
# <<
# 	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1
vs$(PDBVER)\$(CFG)\$(PLAT)\test_thctype.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\test_thctype.obj $(libthai_thctype_OBJS)
vs$(PDBVER)\$(CFG)\$(PLAT)\test_thcell.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\test_thcell.obj $(libthai_thcell_OBJS) $(libthai_thctype_OBJS)
vs$(PDBVER)\$(CFG)\$(PLAT)\test_thinp.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\test_thinp.obj $(libthai_thinp_OBJS) $(libthai_thcell_OBJS) $(libthai_thctype_OBJS)
vs$(PDBVER)\$(CFG)\$(PLAT)\test_thrend.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\test_thrend.obj $(libthai_thrend_OBJS) $(libthai_thcell_OBJS) $(libthai_thctype_OBJS)
vs$(PDBVER)\$(CFG)\$(PLAT)\test_thstr.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\test_thstr.obj $(libthai_thstr_OBJS) $(libthai_thctype_OBJS)
vs$(PDBVER)\$(CFG)\$(PLAT)\thsort.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\thsort.obj $(libthai_thcoll_OBJS) $(libthai_thctype_OBJS)
vs$(PDBVER)\$(CFG)\$(PLAT)\test_thbrk.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\test_thbrk.obj $(libthai_thbrk_OBJS:brk-common.obj=brk-common-test.obj) $(libthai_thwchar_OBJS) $(libthai_thstr_OBJS) $(libthai_thctype_OBJS)
vs$(PDBVER)\$(CFG)\$(PLAT)\test_thwchar.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\test_thwchar.obj $(libthai_thwchar_OBJS) 
vs$(PDBVER)\$(CFG)\$(PLAT)\test_thwbrk.exe: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\test_thwbrk.obj $(libthai_thwbrk_OBJS) $(libthai_thwchar_OBJS) $(libthai_thbrk_OBJS:brk-common.obj=brk-common-test.obj) $(libthai_thstr_OBJS) $(libthai_thctype_OBJS)

$(libthai_tests_EXES):
	link $(LDFLAGS) $** $(LIBTHAI_DEP_LIBS) -out:$@
	@-if exist $@.manifest mt /manifest $@.manifest /outputresource:$@;1

clean:
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.exe
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.dll
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.pdb
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.ilk
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.lib
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\*.exp
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\thbrk.tri
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\vc$(PDBVER)0.pdb
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests\*.obj
	@-rd vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests
	@if exist vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\tdict.txt del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\tdict.txt
	@if exist vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\thbrk.abm del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\thbrk.abm
	@if exist vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\ rd vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\vc$(PDBVER)0.pdb
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\thai.def
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\*.obj
	@-del /f /q vs$(PDBVER)\$(CFG)\$(PLAT)\libthai.pc
	@-rd vs$(PDBVER)\$(CFG)\$(PLAT)\libthai
