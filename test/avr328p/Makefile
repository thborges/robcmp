ALL=$(patsubst %.rob,out/%,$(wildcard *.rob))
ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALL_TT=$(patsubst %.rob,out/%.tt,$(wildcard *.rob))
ALL_OO=$(patsubst %.rob,out/%.o,$(wildcard *.rob)) out/avr328p.o

ROBCMP=../../robcmp
INCLUDES=-I aux

ifndef OPT
#OPT=-g -O0
OPT=-Oz
endif

LD_FLAGS=-nostdlib -entry=main -L../../lib -Tavr328p.ld ../../lib/avr5.o
LD_FLAGS+=-Bstatic 
LD_FLAGS+=--gc-sections

DEPENDS=${ROBCMP} Makefile
LINK_DEPENDS=out/avr328p.o
SERIAL_DEPENDS=out/aux/serial.o out/aux/avr5mcu.o

all: out ${ALL}

out:
	mkdir -p out/aux

out/avr328p.o : ../../lib/avr328p.rob ${DEPENDS}
	${ROBCMP} -a avr328p ${OPT} -o $@ $<

out/avr328p.ll : ../../lib/avr328p.rob ${DEPENDS}
	${ROBCMP} -a avr328p ${OPT} $< > $@

.SECONDARY:
out/%.o : %.rob out/avr328p.o ${DEPENDS}
	${ROBCMP} -a avr328p ${OPT} ${INCLUDES} -o $@ $<

out/%.ll : %.rob ${DEPENDS}
	${ROBCMP} -a avr328p ${OPT} ${INCLUDES} $< > $@

out/%.tt : %.rob ${DEPENDS}
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

out/itoa : out/itoa.o ${SERIAL_DEPENDS} ${LINK_DEPENDS}
out/uart : out/uart.o ${SERIAL_DEPENDS} ${LINK_DEPENDS}
out/% : out/%.o ${LINK_DEPENDS} 
	ld.lld ${LD_FLAGS} $^ -o $@

test: ${ALL_TT}

clean:
	rm -f ${ALL} ${ALL_LL} ${ALL_OO} ${SERIAL_DEPENDS}

