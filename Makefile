LLVMFLAGS=$(shell llvm-config --cxxflags)
LLVMLIBS=$(shell llvm-config --ldflags --libs all) -lpthread -ldl -lcurses
 
FLAGS=-O3 -DYYERROR_VERBOSE
#DFLAGS=-ggdb -O0

CPPS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
YACS=rob_y.o
LEXS=rob_l.o

all: robcmp

%_l.cpp: %.l
	lex -o $@ $<

%_y.cpp: %.y
	bison -d -o $@ $<

robcmp: ${YACS} ${LEXS} ${CPPS}
	g++ ${FLAGS} ${DFLAGS} *.o ${LLVMLIBS} -o robcmp

%.o: %.cpp
	g++ ${LLVMFLAGS} ${FLAGS} ${DFLAGS} -c $< -o $@

clean:
	rm -f rob_y.cpp rob_l.cpp rob_y.hpp *.o


