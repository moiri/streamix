SHELL := /bin/bash

C_DIR = streamix-c
RTS_DIR = streamix-rts
GRAPH_DIR = streamix-graph2c
SIA_DIR = streamix-sia
EXAMPLE_DIR = examples

#EXAMPLES = $(wildcard $(EXAMPLE_DIR)/*/.)
EXAMPLES = $(EXAMPLE_DIR)/copy/.\
		   $(EXAMPLE_DIR)/merge/.\
		   $(EXAMPLE_DIR)/class/.\
		   $(EXAMPLE_DIR)/din/.\
		   $(EXAMPLE_DIR)/dout/.\
		   $(EXAMPLE_DIR)/tb/. \
		   $(EXAMPLE_DIR)/tt/.

PROJECTS = $(C_DIR) $(RTS_DIR) $(GRAPH_DIR) $(SIA_DIR)

TOPTARGETS := all clean install

$(TOPTARGETS): $(PROJECTS)
$(PROJECTS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

examples: $(EXAMPLES)
$(EXAMPLES):
	$(MAKE) -C $@ clean
	$(MAKE) -C $@

test:
	@for elem in $(EXAMPLES); do \
		$(MAKE) -C $$elem test; \
	done

.PHONY: $(TOPTARGETS) $(PROJECTS) examples test $(EXAMPLES)
