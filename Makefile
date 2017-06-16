SHELL := /bin/bash

C_DIR = streamix-c
RTS_DIR = streamix-rts
GRAPH_DIR = streamix-graph2c

.PHONY: all clean install

all:
	cd $(C_DIR) && $(MAKE)
	cd $(RTS_DIR) && $(MAKE)
	cd $(GRAPH_DIR) && $(MAKE)

clean:
	cd $(C_DIR) && $(MAKE) clean
	cd $(RTS_DIR) && $(MAKE) clean
	cd $(GRAPH_DIR) && $(MAKE) clean
	rm -rf $(BIN_DIR)

install:
	cd $(C_DIR) && $(MAKE) install
	cd $(RTS_DIR) && $(MAKE) install
	cd $(GRAPH_DIR) && $(MAKE) install
