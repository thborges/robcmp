CC=clang++

LLVMFLAGS=$(shell llvm-config --cxxflags)
LLVMLIBS=$(shell llvm-config --ldflags --libs all) -lpthread -ldl -lncurses

COMPILER_NAME=$(shell basename "${PWD}")
 
#FLAGS=-O3 -DYYERROR_VERBOSE -fexceptions -Wno-deprecated-register
DFLAGS=-ggdb -O0

CPPS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
YACS=$(patsubst %.y,%_y.o,$(wildcard *.y))
LEXS=$(patsubst %.l,%_l.o,$(wildcard *.l))

all: $(COMPILER_NAME)

%_l.cpp: %.l
	lex -o $@ $<

%_y.cpp: %.y
	bison --defines=bison.hpp -o $@ $<

$(COMPILER_NAME): ${YACS} ${LEXS} ${CPPS}
	${CC} ${FLAGS} ${DFLAGS} *.o ${LLVMLIBS} -o $@

%.o: %.cpp node.h
	${CC} ${LLVMFLAGS} ${FLAGS} ${DFLAGS} -c $< -o $@

clean:
	rm -f *_y.cpp *_l.cpp bison.hpp *.o

#.SILENT:

