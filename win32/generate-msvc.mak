# NMake Makefile portion for code generation and
# intermediate build directory creation
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.

vs$(PDBVER)\$(CFG)\$(PLAT)\libthai\thai.def: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai ..\src\libthai.def
	@echo Generating $@...
	@echo EXPORTS>$@
	@type ..\src\libthai.def>>$@

# Generate compbined Thai Dictionary text file
vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\tdict.txt: ..\data\tdict-*.txt
	@echo Generating $@...
	@if not exist $(@D) $(MAKE) /f Makefile.vc CFG=$(CFG) $(@D)
	@for %f in ($**) do @type %f>>$@

# Copy ..\data\thbrk.abm needed to generate Thai dictionary data file
vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\thbrk.abm: ..\data\thbrk.abm
	@echo Copying $**...
	@if not exist $(@D) $(MAKE) /f Makefile.vc CFG=$(CFG) $(@D)
	@copy $** $@

# Generate Thai dictionary data file
vs$(PDBVER)\$(CFG)\$(PLAT)\thbrk.tri: vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\tdict.txt vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\thbrk.abm
	@echo Generating $@...
	$(TRIETOOL) -p $(@D)\libthai-data thbrk add-list -e utf-8 vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data\tdict.txt
	@move $(@D)\libthai-data\$(@F) $@

# Create the build directories
vs$(PDBVER)\$(CFG)\$(PLAT)\libthai	\
vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-data	\
vs$(PDBVER)\$(CFG)\$(PLAT)\libthai-tests:
	@-mkdir $@

# Generate pkg-config files
vs$(PDBVER)\$(CFG)\$(PLAT)\libthai.pc:
	@call create-pc.bat $@ $(LIBTHAI_VERSION) $(PREFIX)

