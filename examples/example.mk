SHELL := /bin/bash

PROJECT = $(notdir $(shell pwd))
BOXGEN = boxgen
GENPATH = build
FORMAT = graphml

OUTGRAPH_NAME = $(PROJECT).$(FORMAT)
OUTGRAPH = $(GENPATH)/$(OUTGRAPH_NAME)
OUTSRC = $(GENPATH)/$(PROJECT).c \
		 $(GENPATH)/$(BOXGEN).c
OUTINC = $(GENPATH)/$(BOXGEN).h

SOURCES = $(OUTSRC) \
		  boximpl.c

INCLUDES = $(OUTINC) \
		   boximpl.h

INCLUDES_DIR = -I/usr/local/ \
			   -I$(GENPATH) \
			   -I.

LINK_DIR = -L/usr/local/lib

LINK_FILE = -lsmxrts \
			-lpthread \
			-lzlog


CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -O0

all: $(PROJECT).out

smx: $(OUTSRC) $(OUTINC)

# compile with dot stuff and debug flags
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(PROJECT).out

$(PROJECT).out: $(SOURCES) $(INCLUDES)
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES_DIR) $(LINK_DIR) $(LINK_FILE) -o $@

$(OUTSRC) $(OUTINC): $(OUTGRAPH)
	graph2c $^ -p $(GENPATH) -f $(FORMAT)

$(OUTGRAPH): $(PROJECT).smx
	smxc -f $(FORMAT) -p $(GENPATH) -o $(OUTGRAPH_NAME) $^

.PHONY: clean run valgrind

clean:
	rm -rf $(GENPATH)
	rm -f $(PROJECT).out

run:
	./$(PROJECT).out

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./$(PROJECT).out

