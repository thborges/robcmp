ALL=$(patsubst %.rob,out/%,$(wildcard *.rob))
ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALL_TT=$(patsubst %.rob,out/%.tt,$(wildcard *.rob))
ALL_OO=$(patsubst %.rob,out/%.o,$(wildcard *.rob)) out/avr328p.o

ROBCMP=../../robcmp
OPT=-g -O0
#OPT=-Oz

#LD_FLAGS=-nostdlib -entry=main -L../../lib -Bstatic -Tavr328p.ld -Tdata=0x800100 ../../lib/avr5.o
LD_FLAGS=-nostdlib -entry=main -L../../lib -Tavr5.xn -Tdata=0x800100 ../../lib/avr5.o
#LD_FLAGS+=-Bstatic 
LD_FLAGS+=--gc-sections

all: out ${ALL}

out:
	mkdir -p out

clean:
	rm -f ${ALL} ${ALL_LL} ${ALL_OO}

out/avr328p.o : ../../lib/avr328p.rob
	${ROBCMP} -a avr328p ${OPT} -o $@ $<

out/avr328p.ll : ../../lib/avr328p.rob
	${ROBCMP} -a avr328p ${OPT} $< > $@

.SECONDARY:
out/%.o : %.rob out/avr328p.o ${ROBCMP} Makefile
	${ROBCMP} -a avr328p ${OPT} -o $@ $<

out/%.ll : %.rob ${ROBCMP} Makefile
	${ROBCMP} -a avr328p ${OPT} $< > $@

out/%.tt : %.rob
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

out/% : out/%.o out/avr328p.o
	@#ld.lld ${LD_FLAGS} $^ -o $@
	avr-ld ${LD_FLAGS} $^ -o $@


test: ${ALL_TT}


