# NMake Makefile portion for displaying config info

THAI_DATA_BUILT = yes

!if "$(LIB_ONLY)" == "1"
THAI_DATA_BUILT = no
!endif

!if "$(CFG)" == "release"
BUILD_TYPE = release
!else
BUILD_TYPE = debug
!endif

build-info-libthai:
	@echo.
	@echo =========================
	@echo Configuration for libthai
	@echo =========================
	@echo Thai dictionary data built: $(THAI_DATA_BUILT)

all-build-info: build-info-libthai
	@echo.
	@echo ----------------
	@echo Other build info
	@echo ----------------
	@echo Build Type: $(BUILD_TYPE)

help:
	@echo.
	@echo ============================
	@echo Building libthai Using NMake
	@echo ============================
	@echo nmake /f Makefile.vc CFG=[release^|debug] ^<PREFIX=PATH^> OPTION=1 ...
	@echo.
	@echo Where:
	@echo ------
	@echo CFG: Required, use CFG=release for an optimized build and CFG=debug
	@echo for a debug build.  PDB files are generated for all builds.
	@echo.
	@echo PREFIX: Optional, the path where dependent libraries and tools may be
	@echo found, default is ^$(srcrootdir)\..\vs^$(short_vs_ver)\^$(platform),
	@echo where ^$(short_vs_ver) is 12 for VS 2013, 14 for VS 2015 and so on; and
	@echo ^$(platform) is Win32 for 32-bit builds and x64 for x64 builds.
	@echo.
	@echo OPTION: Optional, may be any of the following, use OPTION=1 to enable;
	@echo multiple OPTION's may be used.  If no OPTION is specified, a default
	@echo libthai is built with Thai dictionary data.  Note that generating Thai
	@echo dictionary requires trietool.exe from libdatrie, which requires libiconv
	@echo to run.
	@echo ======
	@echo LIB_ONLY:
	@echo Do not generate Thai dctionary data.  This eliminates the need for trietool.exe.
	@echo ======
	@echo A 'clean' target is supported to remove all generated files, intermediate
	@echo object files and binaries for the specified configuration.
	@echo.
	@echo A 'tests' target is supported to build and run the test programs as well.
	@echo.
	@echo An 'install' target is supported to copy the build (DLLs, built data,
	@echo along with LIBs) to appropriate locations under ^$(PREFIX).
	@echo ======
	@echo.
