CC=/usr/bin/clang++

LLVMFLAGS=$(shell llvm-config-9 --cxxflags)
LLVMLIBS=$(shell llvm-config-9 --ldflags --libs all) -lpthread -ldl -lncurses

COMPILER_NAME=$(shell basename "${PWD}")

SRC = src
BIN = build
 
FLAGS=-O2 -DYYERROR_VERBOSE -fexceptions -Wno-deprecated-register -Wno-unused-function
DFLAGS=-ggdb -O0

CPPS=$(patsubst %.cpp,%.o,$(wildcard ${SRC}/*.cpp))
YACS=$(patsubst %.y,%_y.o,$(wildcard ${SRC}/*.y))
LEXS=$(patsubst %.l,%_l.o,$(wildcard ${SRC}/*.l))

all: $(COMPILER_NAME)

%_l.cpp: %.l
	lex -o $@ $<

%_y.cpp: %.y
	bison --defines=$(SRC)/bison.hpp -o $@ $<

$(COMPILER_NAME): ${YACS} ${LEXS} ${CPPS}
	${CC} -std=c++11 ${FLAGS} ${DFLAGS} ${SRC}/*.o ${LLVMLIBS} -o $(BIN)/$@

%.o: %.cpp
	${CC} -std=c++11 ${LLVMFLAGS} ${FLAGS} ${DFLAGS} -c $< -o $@

clean:
	rm -f ${SRC}/*_y.cpp ${SRC}/*_l.cpp ${SRC}/bison.hpp ${SRC}/*.o

#.SILENT:
