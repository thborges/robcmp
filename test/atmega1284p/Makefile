ALL=$(patsubst %.rob,out/%,$(wildcard *.rob))
ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALL_TT=$(patsubst %.rob,%.tt,$(wildcard *.rob))
ALL_OO=$(patsubst %.rob,out/%.o,$(wildcard *.rob)) out/atmega1284p.o

ROBCMP=../../build/robcmp
INCLUDES=-I ../../lib

ifndef OPT
#OPT=-g -O0
OPT=-Oz
endif

LD_FLAGS=-nostdlib -entry=main -L../../lib -Tatmega1284p.ld ../../lib/avr51.o
LD_FLAGS+=-Bstatic 
LD_FLAGS+=--gc-sections
LD_FLAGS+=--lto=thin

DEPENDS=${ROBCMP} Makefile
LINK_DEPENDS=out/atmega1284p.o

all: out test

out:
	mkdir -p out

out/atmega1284p.o : ../../lib/atmega1284p.rob ${DEPENDS}
	${ROBCMP} -a atmega1284p ${OPT} -o $@ $<

out/atmega1284p.ll : ../../lib/atmega1284p.rob ${DEPENDS}
	${ROBCMP} -a atmega1284p ${OPT} $< > $@

.SECONDARY:
out/%.o : %.rob out/atmega1284p.o ${DEPENDS}
	${ROBCMP} -bdep -a atmega1284p ${OPT} ${INCLUDES} -o $@ $<

out/%.ll : %.rob ${DEPENDS}
	${ROBCMP} -bdep -a atmega1284p ${OPT} ${INCLUDES} $< > $@

%.tt : %.rob ${DEPENDS}
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

out/% : out/%.o ${LINK_DEPENDS} 
    # exchange here if ld.lld show relocation errors
	ld.lld ${LD_FLAGS} $^ -o $@
	#avr-ld ${LD_FLAGS} $^ -o $@

test: ${ALL_TT}

clean:
	@rm -f ${ALL} ${ALL_LL} ${ALL_OO}

