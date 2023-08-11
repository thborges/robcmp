ALL=$(patsubst %.rob,out/%,$(wildcard *.rob))
ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALL_TT=$(patsubst %.rob,out/%.tt,$(wildcard *.rob))
ALL_OO=$(patsubst %.rob,out/%.o,$(wildcard *.rob))

OS=$(shell uname -o)

ifeq ($(OS), Msys)
ROBCMP=../../build/robcmp.exe
ENTRY=__main
else
ROBCMP=../../build/robcmp
ENTRY=main
endif

ifndef OPT
#OPT=-g -O0
OPT=-Oz
endif

all: out ${ALL}

out:
	mkdir -p out

clean:
	rm -f ${ALL} ${ALL_LL} ${ALL_OO}

.SECONDARY:
out/%.o : %.rob ${ROBCMP} Makefile
	${ROBCMP} ${OPT} -o $@ $<

out/%.ll : %.rob ${ROBCMP} Makefile
	${ROBCMP} ${OPT} $< > $@

out/%.tt : %.rob
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

% : %.o
	ld.lld -e ${ENTRY} $< -o $@

test: ${ALL_TT}


