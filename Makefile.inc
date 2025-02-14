# PYTHIA configuration file.
# Generated on Mon Jan 7 10:59:49 STD 2019 with the user supplied options:

# Install directory prefixes.
PY_HOME=/home/wxie/local_pkgs/anaconda3/envs/brian2
PREFIX_BIN=$(PY_HOME)/bin
PREFIX_INCLUDE=$(PY_HOME)/include
PREFIX_LIB=$(PY_HOME)/lib
PREFIX_SHARE=$PY_HOME/share/Pythia8

# Compilation flags (see ./configure --help for further documentation).
ENABLE_SHARED=false
CXX=g++
CXX_COMMON=-O2  -pedantic -W -Wall -Wshadow -fPIC
CXX_SHARED=-shared
CXX_SONAME=-Wl,-soname,
LIB_SUFFIX=.so

# EVTGEN configuration.
EVTGEN_USE=true
EVTGEN_CONFIG=
EVTGEN_BIN=$(PY_HOME)/bin
EVTGEN_INCLUDE=-I$(PY_HOME)/include/EvtGen
EVTGEN_LIB= -L$(PY_HOME)/lib -lEvtGenExternal -lEvtGen -lHepMC3

# ROOT configuration.
ROOT_USE=true
ROOT_BIN=$(ROOTSYS)/bin
ROOT_LIBS=$(ROOTSYS)/lib
ROOT_INCLUDE=$(ROOTSYS)/include
