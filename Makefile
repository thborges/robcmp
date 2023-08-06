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

SCANNERS=src/Language_gen.y src/LanguageUse_gen.y
CPPS=$(patsubst src/%.cpp,src/out/%.o,$(wildcard ${SRC}/*.cpp))
YACS=$(patsubst src/%.y,src/out/%_y.o,$(SCANNERS))
LEXS=$(patsubst src/%.l,src/out/%_l.o,$(wildcard ${SRC}/*.l))

all: src/out $(COMPILER_NAME)

%_l.cpp: %.l
	flex -o $@ $<

.PRECIOUS : %_l.cpp %_y.cpp %_y.hpp
.SECONDARY : $(SCANNERS)

-include $(CPPS:%.o=%.d)

main.cpp : %_l.cpp %_y.cpp %_y.hpp

%_gen.y : src/LanguageHeader.y %.y
	-chmod u+w $@
	cat $^ > $@
	chmod u-w $@

%_y.cpp: %.y
	bison -Wall --defines=$(patsubst %.cpp,%.hpp,$@) -o $@ $<
	$(SED) 's/\"syntax\ error\"/COLOR_RED\ \"syntax\ error\"\ COLOR_RESET/' -i $@
	$(SED) 's/\"syntax\ error:/COLOR_RED\ \"syntax\ error:\"\ COLOR_RESET\"/' -i $@
	$(SED) 's/\"syntax\ error,/COLOR_RED\ \"syntax\ error:\"\ COLOR_RESET\"/' -i $@

$(COMPILER_NAME): ${YACS} ${LEXS} ${CPPS}
	${CC} ${FLAGS} ${DFLAGS} -std=c++17 ${SRC}/out/*.o ${LLVMLIBS} -o $(BIN)/$@

src/out/%.o: src/%.cpp
	${CC} ${LLVMFLAGS} ${FLAGS} ${DFLAGS} -MMD -std=c++17 -c $< -o $@

src/out:
	mkdir ${SRC}/out

clean:
	rm -f ${SRC}/*_y.{hpp,cpp} ${SRC}/*_l.{hpp,cpp} ${SRC}/out/*.o

#.SILENT:
