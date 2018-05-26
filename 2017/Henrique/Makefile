LLVMFLAGS=$(shell llvm-config-3.9 --cxxflags)
LLVMLIBS=$(shell llvm-config-3.9 --ldflags --libs all) -lpthread -ldl 
FLAGS=-O3 -DYYERROR_VERBOSE -fexceptions -Wno-deprecated-register
DFLAGS=-ggdb -O0

all:
	lex -o lexico.c HCompiler.l
	bison -d -o sintatico.c HCompiler.y
	g++ ${LLVMFLAGS} ${FLAGS} ${DFLAGS} ${LLVMLIBS} lexico.c sintatico.c main.cpp -o HCompiler

%.ll: %.txt
	./HCompiler $< > $@

%.s: %.ll
	llc-3.9 $<

%.out: %.s
	gcc $< print.o moves.o  -o $@

