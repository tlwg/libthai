# NMake Makefile snippet for copying the built libraries, utilities and headers to
# a path under $(PREFIX).

install: all
	@if not exist $(PREFIX)\bin\ mkdir $(PREFIX)\bin
	@if not exist $(PREFIX)\lib\pkgconfig\ mkdir $(PREFIX)\lib\pkgconfig
	@if not exist $(PREFIX)\include\thai @mkdir $(PREFIX)\include\thai
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\thai.dll $(PREFIX)\bin
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\thai.pdb $(PREFIX)\bin
	@copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\thai.lib $(PREFIX)\lib
	@for %f in (..\include\thai\*.h) do @copy %f $(PREFIX)\include\thai\%~nxf
	@rem Copy the generated pkg-config file
	@copy /y vs$(PDBVER)\$(CFG)\$(PLAT)\libthai.pc $(PREFIX)\lib\pkgconfig
	@rem Copy the generated Thai dictionary file, if generated
	@if exist vs$(PDBVER)\$(CFG)\$(PLAT)\thbrk.tri if not exist $(PREFIX)\share\libthai\ mkdir $(PREFIX)\share\libthai
	@if exist vs$(PDBVER)\$(CFG)\$(PLAT)\thbrk.tri copy /b vs$(PDBVER)\$(CFG)\$(PLAT)\thbrk.tri $(PREFIX)\share\libthai
