CC=/usr/bin/clang++-15
#CC=/usr/local/bin/clang++

#if your llvm has a sufix, llvm-config-9, put -9 here
LLVMVERSIONNR="-15"

LLVMFLAGS=$(shell llvm-config${LLVMVERSIONNR} --cxxflags) -frtti
LLVMLIBS=$(shell llvm-config${LLVMVERSIONNR} --ldflags --libs all) -lpthread -ldl -lncurses -lz

COMPILER_NAME=$(shell basename "${PWD}")

SRC = src
BIN = .
 
FLAGS=-O2 -DYYERROR_VERBOSE -fexceptions -Wno-deprecated-register -Wno-unused-function
DFLAGS=-ggdb -O0

CPPS=$(patsubst %.cpp,%.o,$(wildcard ${SRC}/*.cpp))
YACS=$(patsubst %.y,%_y.o,$(wildcard ${SRC}/*.y))
LEXS=$(patsubst %.l,%_l.o,$(wildcard ${SRC}/*.l))

all: $(COMPILER_NAME)

%_l.cpp: %.l
	lex -o $@ $<

%_y.cpp: %.y
	bison -Wall --report=state --defines=$(SRC)/bison.hpp -o $@ $<

$(COMPILER_NAME): ${YACS} ${LEXS} ${CPPS}
	${CC} -std=c++11 ${FLAGS} ${DFLAGS} ${SRC}/*.o ${LLVMLIBS} -o $(BIN)/$@

%.o: %.cpp
	${CC} -std=c++11 ${LLVMFLAGS} ${FLAGS} ${DFLAGS} -c $< -o $@

clean:
	rm -f ${SRC}/*_y.cpp ${SRC}/*_l.cpp ${SRC}/bison.hpp ${SRC}/*.o

#.SILENT:
