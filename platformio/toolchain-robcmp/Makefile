LLVM_OBJCOPY=$(shell which llvm-objcopy-20)
ifeq ($(LLVM_OBJCOPY),)
	LLVM_OBJCOPY=$(shell which llvm-objcopy)
endif

LLVM_LD=$(shell which ld.lld-20)
ifeq ($(LLVM_LD),)
	LLVM_LD=$(shell which ld.lld)
endif

LLVM_SIZE=$(shell which llvm-size-20)
ifeq ($(LLVM_SIZE),)
	LLVM_SIZE=$(shell which llvm-size)
endif

ifeq ($(LLVM_LD),)
    $(error "Can't find llvm-ld!")
endif

ifeq ($(LLVM_OBJCOPY),)
    $(error "Can't find llvm-objcopy!")
endif

ifeq ($(LLVM_SIZE),)
    $(error "Can't find llvm-size!")
endif

AVR_GDB=$(shell which avr-gdb)
ifeq ($(AVR_GDB),)
    $(error "Can't find avr-gdb!")
endif

AVR_OBJDUMP=$(shell which avr-objdump)
ifeq ($(AVR_OBJDUMP),)
    $(error "Can't find avr-objdump!")
endif


TOOLS=$(LLVM_OBJCOPY) \
	$(LLVM_LD) \
	$(LLVM_SIZE) \
	$(AVR_GDB) \
	$(AVR_OBJDUMP) \
	$(abspath ../../build/robcmp) \
	$(abspath ../../build/robcmp-simavr-debug)

ifeq ($(OS),Windows_NT)
    uname_S := Windows
else
    uname_S := $(shell uname -s)
endif

ifeq ($(uname_S), Darwin)
	suffix=darwin_$(shell uname -m)
	SED=gsed
	LIBS=$(shell ./libllvmpathosx.sh ${LLVM_LD})
endif
ifeq ($(uname_S), Linux)
	suffix=linux_x86_64
	SED=sed
	LIBS=$(shell ./libllvmpath.sh ${LLVM_LD})
endif

#LIBS += ../../lib/*.ld ../../lib/*.o ../../lib/*.rob

version=$(shell cat version)

all: bin lib ../toolchain-robcmp-${suffix}-${version}.tar.gz

bin:
	mkdir bin

lib:
	mkdir lib

package.json: package-orig.json
	$(SED) s/sed_system_here/$(suffix)/ $< > $@

../toolchain-robcmp-${suffix}-${version}.tar.gz: package.json
	ln -sf $(TOOLS) bin
	ln -sf $(LIBS) lib
	if [ -f bin/ld.lld-20 ]; then cd bin && ln -s ld.lld-20 ld.lld; fi
	if [ -f bin/llvm-objcopy-20 ]; then cd bin && ln -s llvm-objcopy-20 llvm-objcopy; fi
	tar chfz $@ $^ bin lib

clean:
	rm -rf bin lib *.tar.gz package.json
