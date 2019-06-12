SHELL := /bin/bash

PROJECT = $(notdir $(shell pwd))
BOXGEN = boxgen
GENPATH = build
FORMAT = graphml

OUTGRAPH_NAME = $(PROJECT).$(FORMAT)
SIAGRAPH_NAME = sia_$(PROJECT).$(FORMAT)
PNSCGRAPH_NAME = pnsc_$(PROJECT).$(FORMAT)
OUTGRAPH = $(GENPATH)/$(OUTGRAPH_NAME)
SIAGRAPH = $(GENPATH)/$(SIAGRAPH_NAME)
PNSCGRAPH = $(GENPATH)/$(PNSCGRAPH_NAME)
OUTSRC = $(GENPATH)/$(PROJECT).c \
		 $(GENPATH)/$(BOXGEN).c
OUTINC = $(GENPATH)/$(BOXGEN).h

SOURCES = $(OUTSRC) \
		  boximpl.c

INCLUDES = $(OUTINC) \
		   boximpl.h

INCLUDES_DIR = -I/usr/local/ \
			   -I/usr/local/include/libsmx \
			   -I/usr/include/libxml2 \
			   -I/usr/include/libmongoc-1.0 \
			   -I/usr/include/libbson-1.0 \
			   -I$(GENPATH) \
			   -I.

LINK_DIR = -L/usr/local/lib \
		   -L/usr/local/lib/libsmx

LINK_FILE = -lsmxrts \
			-lpthread \
			-lxml2 \
			-lsmxmongo \
			-lbson \
			-lmongoc \
			-lzlog


CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -O0

all: $(PROJECT).out

smx: $(OUTSRC) $(OUTINC)

sia: $(SIAGRAPH)

# compile with dot stuff and debug flags
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(PROJECT).out

$(PROJECT).out: $(SOURCES) $(INCLUDES)
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES_DIR) $(LINK_DIR) $(LINK_FILE) -o $@

$(SIAGRAPH): $(PNSCGRAPH)
	smxsia -f $(FORMAT) -o $@ $^ $(GENPATH)/sia/*

$(PNSCGRAPH) $(OUTSRC) $(OUTINC): $(OUTGRAPH)
	graph2c $^ -p $(GENPATH) -f $(FORMAT)

$(OUTGRAPH): $(PROJECT).smx
	smxc -f $(FORMAT) -p $(GENPATH) $(SIA_INPUT) -o $(OUTGRAPH_NAME) $^


.PHONY: clean run valgrind

clean: clean_run
	rm -rf $(GENPATH)
	rm -f $(PROJECT).out

clean_run:
	rm -f out/*
	rm -f log/*

run:
	./$(PROJECT).out

test: clean_run run
	./test.sh

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./$(PROJECT).out

