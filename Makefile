SHELL := /bin/bash

C_DIR = streamix-c
RTS_DIR = streamix-rts
GRAPH_DIR = streamix-graph2c
SIA_DIR = streamix-sia-lang
EXAMPLE_DIR = examples

EXAMPLES = $(wildcard $(EXAMPLE_DIR)/*/.)
PROJECTS = $(C_DIR) $(RTS_DIR) $(GRAPH_DIR) $(SIA_DIR)

TOPTARGETS := all clean install

$(TOPTARGETS): $(PROJECTS)
$(PROJECTS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

examples: $(EXAMPLES)
$(EXAMPLES):
	$(MAKE) -C $@ clean
	$(MAKE) -C $@

.PHONY: $(TOPTARGETS) $(PROJECTS) examples $(EXAMPLES)
