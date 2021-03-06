SHELL := /bin/bash

###############################################################################
# START CUTOMIZATION HERE
# Changes in this area should be enough to customize the building process.
# If other changes are necessary, feel free to do so ;)
###############################################################################

# list the external libraries prefixed with -l
EXT_LIBS =

# list the external libraries directories prefixed with -L
EXT_LIBS_DIR =

# list the external include files prefixed with -I
EXT_INCS_DIR =

# list of libraries required for the profiler
#PROFILER_LIBS = -lsmxmongo -lmongoc -lbson

# list include directories required for the profiler
#PROFILER_INCS_DIR = -I/usr/include/libmongoc-1.0 -I/usr/include/libbson-1.0

###############################################################################
# END CUTOMIZATION HERE
###############################################################################

PROJECT = merge

GENPATH = build
BOXIMPL = boxes/*
FORMAT = graphml

BIN_PATH = /opt/smx/bin

OUTGRAPH_NAME = $(PROJECT).$(FORMAT)
SIAGRAPH_NAME = sia_$(PROJECT).$(FORMAT)
PNSCGRAPH_NAME = pnsc_$(PROJECT).$(FORMAT)
OUTGRAPH = $(GENPATH)/$(OUTGRAPH_NAME)
SIAGRAPH = $(GENPATH)/$(SIAGRAPH_NAME)
PNSCGRAPH = $(GENPATH)/$(PNSCGRAPH_NAME)
OUTSRC = $(PROJECT).c
OUTINC = $(BOXIMPL)/include/*_sig.h

SOURCES = $(OUTSRC)

INCLUDES = $(BOXIMPL)/include/*.h

INCLUDES_DIR = -I/usr/local/ \
	-I/opt/smx/include \
	-I/usr/include/libxml2 \
	-I. $(BOX_INC_DIR) $(PROFILER_INCS_DIR) $(EXT_INCS_DIR)

LINK_DIR = -L/usr/local/lib \
	-L/opt/smx/lib $(BOX_LIB_DIR) $(EXT_LIBS_DIR)

LINK_FILE = -lsmxrts \
	-lpthread \
	-lxml2 \
	-lzlog $(LIBS) $(PROFILER_LIBS) $(EXT_LIBS)

CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -O0

all: $(PROJECT)

smx: $(OUTSRC) $(OUTINC)

sia: $(SIAGRAPH)

# compile with dot stuff and debug flags
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(PROJECT)

$(PROJECT): $(SOURCES) $(INCLUDES) boximpl
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES_DIR) $(LINK_DIR) $(LINK_FILE) -o $@

boximpl: $(BOXIMPL) setboxpaths
$(BOXIMPL):
	$(MAKE) -C $@

setboxpaths:
	$(eval LIBS_A = $(wildcard $(BOXIMPL)/lib/*.a))
	$(eval LIBS = $(patsubst %, -l:%, $(notdir $(LIBS_A))))
	$(eval BOX_INC_DIR_RAW = $(wildcard $(BOXIMPL)/include))
	$(eval BOX_INC_DIR = $(patsubst %, -I%, $(BOX_INC_DIR_RAW)))
	$(eval BOX_LIB_DIR_RAW = $(wildcard $(BOXIMPL)/lib))
	$(eval BOX_LIB_DIR = $(patsubst %, -L%, $(BOX_LIB_DIR_RAW)))

$(SIAGRAPH): $(PNSCGRAPH)
	$(BIN_PATH)/smxsia -f $(FORMAT) -o $@ $^ $(GENPATH)/sia/*

$(PNSCGRAPH) $(OUTSRC) $(OUTINC): $(OUTGRAPH)
	$(BIN_PATH)/smxrtsp $^ -p $(GENPATH) -f $(FORMAT)

$(OUTGRAPH): $(PROJECT).smx
	$(BIN_PATH)/smxc -f $(FORMAT) -p $(GENPATH) $(SIA_INPUT) -o $(OUTGRAPH_NAME) $^


.PHONY: clean run valgrind boximpl $(BOXIMPL) setboxpaths

clean: clean_run
	rm -rf $(GENPATH)
	rm -f $(PROJECT)
	rm -f $(PROJECT).c
	rm -f $(BOXIMPL)/include/*_sig.h
	rm -rf $(BOXIMPL)/lib
	rm -rf $(BOXIMPL)/obj

clean_run:
	rm -f out/*
	rm -f log/*

run:
	./$(PROJECT)

test: clean_run run
	./test.sh

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./$(PROJECT)

