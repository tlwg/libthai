Instructions for building libthai on Visual Studio
==================================================
Building the libthai on Windows is now supported using Visual Studio.

You will need the following items to build libthai using Visual Studio:
-libiconv (including the libcharset headers and libraries) if building trietool.exe

Invoke the build by issuing the command:
nmake /f Makefile.vc CFG=[release|debug] [PREFIX=...] <option1=1 option2=1 ...>
where:

CFG: Required.  Choose from a release or debug build.  Note that
     all builds generate a .pdb file for each .dll and .exe built--this refers
     to the C/C++ runtime that the build uses.

PREFIX: Optional.  Base directory of where the third-party headers, libraries
        and needed tools can be found, i.e. headers in $(PREFIX)\include,
        libraries in $(PREFIX)\lib and tools in $(PREFIX)\bin.  If not
        specified, $(PREFIX) is set as $(srcroot)\..\vs$(X)\$(platform), where
        $(platform) is win32 for 32-bit builds or x64 for 64-bit builds, and
        $(X) is the short version of the Visual Studio used, as follows:
        2008: 9
        2010: 10
        2012: 11
        2013: 12
        2015, 2017, 2019: 14

Explanation of options, set by <option>=1 unless otherwise noted:
-----------------------------------------------------------------
LIB_ONLY: Disables building the Thai dictionary data file, which eliminates the need for
          trietool.exe, which requires libiconv with libcharset to run.

LIBDATRIE_INCLUDE_BASE: Base directory where the headers of libdatrie can be found, which
                        is $(LIBDATRIE_INCLUDE_BASE)\datrie.  If not specified, 
                        $(PREFIX)\include is used for this value.

LIBDATRIE_LIB: Full path or name of .lib of libdatrie, if datrie.lib cannot be found in
               in the paths indicated by %LIB% or $(PREFIX)\lib.
TRIETOOL: Location of the trietool.exe program from libdatrie, if LIB_ONLY is not specified.
          If not specified, $(PREFIX)\bin\trietool.exe will be used for this value.

If you encounter C4819 warnings and/or C2001 errors (newline in constant), you will need to
set your system locale to English (United States) using Control Panel->Time and Region Settings->
Region->System Management->Encoding for non-Unicode programs, reboot, and clean up and retry
the build.  Note that the /utf-8 compiler flag in Visual Studio 2015 or later is not sufficient.
Please note that warning C4819 should not be ignored, as it is an indication that the build
might have been done incorrectly.

An 'install' target is provided to copy the built items and public headers to appropriate
locations under $(PREFIX), a 'clean' target is provided to remove all the items that are
created during the build, and a 'tests' target is provided to build and run the test programs.
Note that it is necessary that the libdatrie DLL is found in %PATH% or is copied to $(outdir)
to run the test_thbrk and test_thwbrk test programs, if building against a DLL build of
libdatrie.
