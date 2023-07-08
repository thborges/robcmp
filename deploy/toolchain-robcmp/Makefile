LLVM_OBJCOPY=$(shell which llvm-objcopy-16)
ifeq ($(LLVM_OBJCOPY),)
	LLVM_OBJCOPY=$(shell which llvm-objcopy)
endif

LLVM_LD=$(shell which ld.lld-16)
ifeq ($(LLVM_LD),)
	LLVM_LD=$(shell which ld.lld)
endif

TOOLS=$(LLVM_OBJCOPY) $(LLVM_LD) ../../robcmp

ifeq ($(OS),Windows_NT)
    uname_S := Windows
else
    uname_S := $(shell uname -s)
endif

ifeq ($(uname_S), Darwin)
	suffix=darwin_x86_64
	SED=gsed
endif
ifeq ($(uname_S), Linux)
	suffix=linux_x86_64
	SED=sed
	LIBS=$(shell ./libllvmpath ${LLVM_LD})
endif

version=$(shell cat version)

all: bin lib toolchain-robcmp-${suffix}-${version}.tar.gz

bin:
	mkdir bin

lib:
	mkdir lib

package.json: package-orig.json
	$(SED) s/sed_system_here/$(suffix)/ $< > $@

toolchain-robcmp-${suffix}-${version}.tar.gz: package.json
	for f in $(TOOLS); do cp $$f bin; done;
	for f in $(LIBS); do cp $$f lib; done;
	if [ -f bin/ld.lld-16 ]; then cd bin && ln -s ld.lld-16 ld.lld; fi
	if [ -f bin/llvm-objcopy-16 ]; then cd bin && ln -s llvm-objcopy-16 llvm-objcopy; fi
	tar cfz $@ $^ bin/* lib/*

clean:
	rm -rf bin lib *.tar.gz package.json
