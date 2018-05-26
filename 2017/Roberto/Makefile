LLVMFLAGS=$(shell llvm-config-3.9 --cxxflags)
LLVMLIBS=$(shell llvm-config-3.9 --ldflags --libs all) -lpthread -ldl #-lncurses
 
FLAGS=-O3 -DYYERROR_VERBOSE -fexceptions -Wno-deprecated-rigister
DFLAGS=-ggdb -O0


all:
	lex -o lexico.c casa_rob.l
	bison -d -o sintatico.c casa_rob.y
	g++ ${LLVMFLAGS} ${FLAGS} ${DFLAGS} ${LLVMLIBS} lexico.c sintatico.c main.cpp -o casacomp

%.ll: %.txt
	./casacomp $< >$@
%.s: %.ll
	llc-3.9 $< 
%.out: %.s
	gcc $< moves.o print.o -o $@
clean:
	rm -f casacomp *.ll *.s *.out
