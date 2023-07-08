LLVM_LDFLAGS=-L/usr/local/lib
CC=/usr/local/robllvm/bin/clang++
LLVMCONFIG=/usr/local/robllvm/bin/llvm-config
SYSROOT=-isysroot `xcrun -sdk macosx --show-sdk-path`

LLVMFLAGS=$(shell ${LLVMCONFIG} --cxxflags) -frtti ${SYSROOT}
LLVMLIBS=$(shell ${LLVMCONFIG} --ldflags --libs all) -lpthread -ldl -lncurses -lz -lzstd ${LLVM_LDFLAGS} ${SYSROOT}

COMPILER_NAME=$(shell basename "${PWD}")

SRC = src
BIN = .
 
FLAGS=-O3 -march=native -DYYERROR_VERBOSE -fexceptions
DFLAGS=-ggdb -O0

CPPS=$(patsubst %.cpp,%.o,$(wildcard ${SRC}/*.cpp))
YACS=$(patsubst %.y,%_y.o,$(wildcard ${SRC}/*.y))
LEXS=$(patsubst %.l,%_l.o,$(wildcard ${SRC}/*.l))

all: $(COMPILER_NAME)

%_l.cpp: %.l
	lex -o $@ $<

%_y.cpp: %.y
	bison -Wall --report=state --defines=$(SRC)/bison.hpp -o $@ $<
	gsed 's/\"syntax\ error\"/COLOR_RED\ \"syntax\ error\"\ COLOR_RESET/' -i $@
	gsed 's/\"syntax\ error:/COLOR_RED\ \"syntax\ error:\"\ COLOR_RESET\"/' -i $@
	gsed 's/\"syntax\ error,/COLOR_RED\ \"syntax\ error:\"\ COLOR_RESET\"/' -i $@

$(COMPILER_NAME): ${YACS} ${LEXS} ${CPPS}
	${CC} -std=c++11 ${FLAGS} ${DFLAGS} ${SRC}/*.o ${LLVMLIBS} -o $(BIN)/$@

%.o: %.cpp
	${CC} -std=c++11 ${LLVMFLAGS} ${FLAGS} ${DFLAGS} -c $< -o $@

clean:
	rm -f ${SRC}/*_y.cpp ${SRC}/*_l.cpp ${SRC}/bison.hpp ${SRC}/*.o

#.SILENT:
