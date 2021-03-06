SHELL := /bin/bash

###############################################################################
# START CUTOMIZATION HERE
# Changes in this area should be enough to customize the building process.
# If other changes are necessary, feel free to do so ;)
###############################################################################

# The library name must start with lib and cannot contain any special characters
# (only use characters from [a-zA-Z0-9]). Make sure that the library name is
# unique. Good practice is to use the prefix smxbox.
LIBNAME = libsmxboxm

# Each include path must be preceeded by the gcc option -I
MY_INCLUDES =

###############################################################################
# END CUTOMIZATION HERE
###############################################################################

LOC_INC_DIR = include
LOC_SRC_DIR = src
LOC_OBJ_DIR = obj
LOC_LIB_DIR = lib

DEB_DIR = deb
DEBS = $(DEB_DIR)/$(LIBNAME)_0.1-0 \
	   $(DEB_DIR)/$(LIBNAME)-dev

TGT_INCLUDE = /opt/smx/include
TGT_LIB = /opt/smx/lib

STATLIB = $(LOC_LIB_DIR)/$(LIBNAME).a
DYNLIB = $(LOC_LIB_DIR)/$(LIBNAME).so

SOURCES = $(wildcard $(LOC_SRC_DIR)/*.c)
OBJECTS := $(patsubst $(LOC_SRC_DIR)/%.c, $(LOC_OBJ_DIR)/%.o, $(SOURCES))

INCLUDES = $(LOC_INC_DIR)/*.h

INCLUDES_DIR = -I$(LOC_INC_DIR) \
			   -I/usr/include/libxml2 \
			   -I$(TGT_INCLUDE) \
			   -I. $(MY_INCLUDES)

CFLAGS = -Wall -fPIC
DEBUG_FLAGS = -g -O0

CC = gcc

all: $(STATLIB) $(DYNLIB)

# compile with debug flags
debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

$(STATLIB): $(OBJECTS)
	mkdir -p $(LOC_LIB_DIR)
	ar -cq $@ $^

$(DYNLIB): $(OBJECTS)
	$(CC) -shared $^ -o $@

# compile project
$(OBJECTS): $(SOURCES) $(INCLUDES)
	mkdir -p $(LOC_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES_DIR) $(LINK_FILE) -c $< -o $@

.PHONY: clean install doc deb $(DEBS)

install:
	mkdir -p $(TGT_LIB) $(TGT_INCLUDE)
	cp -a $(LOC_INC_DIR)/*.h $(TGT_INCLUDE)/.
	cp -a $(LOC_LIB_DIR)/$(LIBNAME).a $(TGT_LIB)/.
	cp -a $(LOC_LIB_DIR)/$(LIBNAME).so $(TGT_LIB)/.

clean:
	rm -f $(LOC_OBJ_DIR)/*
	rm -f $(LOC_LIB_DIR)/*
	rm -rf $(DEB_DIR)/*/usr

doc:
	doxygen .doxygen

deb: clean all $(DEBS)
$(DEBS):
	mkdir -p $@$(TGT_LIB)
	cp $(LOC_LIB_DIR)/$(LIBNAME).so $@$(TGT_LIB)/.
	@if [[ $@ == *-dev ]]; then \
		mkdir -p $@$(TGT_INCLUDE); \
		cp $(LOC_INC_DIR)/* $@$(TGT_INCLUDE)/.; \
		echo "cp $(LOC_INC_DIR)/* $@$(TGT_INCLUDE)/."; \
	fi
	dpkg-deb -b $@
