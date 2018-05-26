LLVMFLAGS=$(shell llvm-config-3.9 --cxxflags)
LLVMLIBS=$(shell llvm-config-3.9 --ldflags --libs all) -lpthread -ldl 
FLAGS=-O3 -DYYERROR_VERBOSE -fexceptions -Wno-deprecated-register
DFLAGS=-ggdb -O0

all:
	lex -o lexico.c calculadora.l
	bison -d -o sintatico.c calculadora.y
	g++ ${LLVMFLAGS} ${FLAGS} ${DFLAGS} ${LLVMLIBS} roman_parser.c decimalParser.c lexico.c sintatico.c main.cpp -o calccomp

%.ll: %.txt
	./calccomp $< > $@

%.s: %.ll
	llc-3.9 $<

%.out: %.s
	gcc $< print.o moves.o  -o $@

