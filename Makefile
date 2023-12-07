# Makefile is a part of the PYTHIA event generator.
# Copyright (C) 2018 Torbjorn Sjostrand.
# PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
# Please respect the MCnet Guidelines, see GUIDELINES for details.
# Author: Philip Ilten, September 2014.
#
# This is is the Makefile used to build PYTHIA examples on POSIX systems.
# Example usage is:
#     make main01
# For help using the make command please consult the local system documentation,
# i.e. "man make" or "make --help".

################################################################################
# VARIABLES: Definition of the relevant variables from the configuration script.
################################################################################

# Set the shell.
SHELL=/usr/bin/env bash

# Include the configuration.
-include Makefile.inc

# Handle GZIP support.
GZIP_INC=
GZIP_FLAGS=
ifeq ($(GZIP_USE),true)
  GZIP_INC+= -DGZIPSUPPORT -I$(GZIP_INCLUDE)
  GZIP_FLAGS+= -L$(GZIP_LIB) -Wl,-rpath,$(GZIP_LIB) -lz
endif

# Check distribution (use local version first, then installed version).
CXX_COMMON:=-I$(PREFIX_INCLUDE) $(CXX_COMMON)
CXX_COMMON+= -L$(PREFIX_LIB) -Wl,-rpath,$(PREFIX_LIB) -lpythia8 -ldl 

################################################################################
# RULES: Definition of the rules used to build the PYTHIA examples.
################################################################################

# Rules without physical targets (secondary expansion for specific rules).
.SECONDEXPANSION:
.PHONY: all clean

# All targets (no default behavior).
all:
	@echo "Usage: make mainXX"

# The Makefile configuration.
Makefile.inc:
	$(error Error: PYTHIA must be configured, please run "./configure"\
                in the top PYTHIA directory)

# PYTHIA libraries.
$(PREFIX_LIB)/libpythia8.a :
	$(error Error: PYTHIA must be built, please run "make"\
                in the top PYTHIA directory)

# Examples without external dependencies.
main% : main%.cc $(PREFIX_LIB)/libpythia8.a
	$(CXX) $< -o $@ $(CXX_COMMON) $(GZIP_INC) $(GZIP_FLAGS)

LcD0ratio: LcD0ratio.C $(PREFIX_LIB)/libpythia8.a
	$(CXX) $< -o $@ -w  -I$(PREFIX_INCLUDE) -I$(ROOT_INCLUDE) $(CXX_COMMON)  $(EVTGEN_INCLUDE) \
		`$(ROOT_BIN)/root-config --cflags`\
		-Wl,-rpath,$(ROOT_LIB) `$(ROOT_BIN)/root-config --glibs` \
		-DEVTGEN_PYTHIA -DEVTGEN_EXTERNAL $(EVTGEN_LIB)

DDbar: DDbar.C $(PREFIX_LIB)/libpythia8.a
	$(CXX) $< -o $@ -w  -I$(PREFIX_INCLUDE) -I$(ROOT_INCLUDE) $(CXX_COMMON)  $(EVTGEN_INCLUDE) \
		`$(ROOT_BIN)/root-config --cflags`\
		-Wl,-rpath,$(ROOT_LIB) `$(ROOT_BIN)/root-config --glibs` \
		-DEVTGEN_PYTHIA -DEVTGEN_EXTERNAL $(EVTGEN_LIB)

# Internally used tests, without external dependencies.
test% : test%.cc $(PREFIX_LIB)/libpythia8.a
	$(CXX) $< -o $@ $(CXX_COMMON) $(GZIP_INC) $(GZIP_FLAGS)

# Clean.
clean:
	rm -f LcD0ratio DDbar; rm -f *.dat;\
	rm -f *~; rm -f \#*; rm -f core*; rm -f *Dct.*; rm -f *.so;
