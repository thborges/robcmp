LLVM_ROOT=/usr/local/robllvm

TOOLS=llvm-ar llvm-as llvm-objcopy llvm-ranlib ld.lld robcmp

TOOLS_BIN=$(patsubst %,bin/%,${TOOLS})

ifeq ($(OS),Windows_NT)
    uname_S := Windows
else
    uname_S := $(shell uname -s)
endif

ifeq ($(uname_S), Darwin)
suffix=darwin_x86_64
endif
ifeq ($(uname_S), Linux)
suffix=linux_x86_64
endif

version=$(shell cat version)

all: toolchain-robcmp-${suffix}-${version}.tar.gz


bin:
	mkdir bin

bin/%:
	cp ${LLVM_ROOT}/bin/$(@F) $@

bin/robcmp:
	cp ../../robcmp bin/

toolchain-robcmp-${suffix}-${version}.tar.gz: ${TOOLS_BIN} package.json
	tar cfz $@ $^

clean:
	rm *.tar.gz
