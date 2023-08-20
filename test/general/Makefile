ALL=$(patsubst %.rob,out/%,$(wildcard *.rob))
ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALL_TT=$(patsubst %.rob,%.tt,$(wildcard *.rob))
ALL_OO=$(patsubst %.rob,out/%.o,$(wildcard *.rob))

OS=$(shell uname -o)

ifeq ($(OS), Msys)
ROBCMP=../../build/robcmp.exe
else
ROBCMP=../../build/robcmp
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

%.tt : %.rob
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

ifeq ($(OS), Msys)
% : %.o
	${LD} -e __main $< -o $@
endif

test: ${ALL_TT}


