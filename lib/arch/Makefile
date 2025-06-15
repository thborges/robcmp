ATDF=$(shell find . -type f -name '*.atdf')
GEN_SVDS=$(patsubst %.atdf,%.svd,$(ATDF))

SVD := $(shell find . -type f -name '*.svd')
DIRS := $(sort $(dir $(SVD)))
ALL_ROBS := $(foreach d,$(DIRS),$(d)regs.rob)

all: pre $(ALL_ROBS)

pre: $(GEN_SVDS)

.SECONDARY:
%.svd : %.atdf
	atdf2svd $< > $@

define SVD_template
$(1)regs.rob: $(wildcard $(1)*.svd) svd2rob.py
	python3 svd2rob.py $$< > $$@
endef

$(foreach d,$(DIRS),$(eval $(call SVD_template,$(d))))

