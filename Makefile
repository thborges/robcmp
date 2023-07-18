# detect OS
uname = $(shell uname)
ifeq ($(uname), Linux)
	SED=$(shell which sed)
endif
ifeq ($(uname), Darwin)
	SYSROOT=-isysroot `xcrun -sdk macosx --show-sdk-path`
	LDFLAGS=-L/usr/local/lib -lz -lzstd -lpthread -ldl -lncurses
	SED=$(shell which gsed)
endif

CC=$(shell which clang++-16)
ifeq ($(CC),)
	CC=$(shell which clang++)
endif

LLVMCONFIG=$(shell which llvm-config-16)
ifeq ($(LLVMCONFIG),)
	LLVMCONFIG=$(shell which llvm-config)
endif

LLVMFLAGS=$(shell ${LLVMCONFIG} --cxxflags) -frtti ${SYSROOT}
LLVMLIBS=$(shell ${LLVMCONFIG} --ldflags --libs all)  ${LDFLAGS} ${SYSROOT}

COMPILER_NAME=$(shell basename "${PWD}")

SRC = src
BIN = .
 
#FLAGS=-O3 -march=native -flto
DFLAGS=-ggdb -O0 -std=c++17

CPPS=$(patsubst src/%.cpp,src/out/%.o,$(wildcard ${SRC}/*.cpp))
YACS=$(patsubst src/%.y,src/out/%_y.o,$(wildcard ${SRC}/*.y))
LEXS=$(patsubst src/%.l,src/out/%_l.o,$(wildcard ${SRC}/*.l))

all: src/out $(COMPILER_NAME)

%_l.cpp: %.l
	lex -o $@ $<

%_y.cpp: %.y
	bison -Wall --report=state --defines=$(SRC)/bison.hpp -o $@ $<
	$(SED) 's/\"syntax\ error\"/COLOR_RED\ \"syntax\ error\"\ COLOR_RESET/' -i $@
	$(SED) 's/\"syntax\ error:/COLOR_RED\ \"syntax\ error:\"\ COLOR_RESET\"/' -i $@
	$(SED) 's/\"syntax\ error,/COLOR_RED\ \"syntax\ error:\"\ COLOR_RESET\"/' -i $@

$(COMPILER_NAME): ${YACS} ${LEXS} ${CPPS}
	${CC} -std=c++11 ${FLAGS} ${DFLAGS} ${SRC}/out/*.o ${LLVMLIBS} -o $(BIN)/$@

src/out/%.o: src/%.cpp
	${CC} -std=c++11 ${LLVMFLAGS} ${FLAGS} ${DFLAGS} -c $< -o $@

src/out:
	mkdir ${SRC}/out

clean:
	rm -f ${SRC}/*_y.cpp ${SRC}/*_l.cpp ${SRC}/bison.hpp ${SRC}/out/*.o

#.SILENT:
.PRECIOUS: bison.hpp
