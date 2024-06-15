ALL=$(patsubst %.rob,out/%,$(wildcard *.rob))
ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALL_TT=$(patsubst %.rob,%.tt,$(wildcard *.rob))
ALL_OO=$(patsubst %.rob,out/%.o,$(wildcard *.rob)) out/avr328p.o

ROBCMP=../../build/robcmp
INCLUDES=-I ../../lib

ifndef OPT
#OPT=-g -O0
OPT=-Oz
endif

LD_FLAGS=-nostdlib -entry=main -L../../lib -Tavr328p.ld ../../lib/avr5.o
LD_FLAGS+=-Bstatic 
LD_FLAGS+=--gc-sections
LD_FLAGS+=--lto=thin

DEPENDS=${ROBCMP} Makefile
LINK_DEPENDS=out/avr328p.o

all: out test

out:
	mkdir -p out

out/avr328p.o : ../../lib/avr328p.rob ${DEPENDS}
	${ROBCMP} -a avr328p ${OPT} -o $@ $<

out/avr328p.ll : ../../lib/avr328p.rob ${DEPENDS}
	${ROBCMP} -a avr328p ${OPT} $< > $@

.SECONDARY:
out/%.o : %.rob out/avr328p.o ${DEPENDS}
	${ROBCMP} -bdep -a avr328p ${OPT} ${INCLUDES} -o $@ $<

out/%.ll : %.rob ${DEPENDS}
	${ROBCMP} -bdep -a avr328p ${OPT} ${INCLUDES} $< > $@

%.tt : %.rob ${DEPENDS}
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

out/% : out/%.o ${LINK_DEPENDS} 
	ld.lld ${LD_FLAGS} $^ -o $@

test: ${ALL_TT}

clean:
	@rm -f ${ALL} ${ALL_LL} ${ALL_OO}

