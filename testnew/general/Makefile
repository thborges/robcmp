ALL=$(patsubst %.rob,out/%,$(wildcard *.rob))
ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALL_TT=$(patsubst %.rob,out/%.tt,$(wildcard *.rob))
ALL_OO=$(patsubst %.rob,out/%.o,$(wildcard *.rob))

ROBCMP=../../robcmp
#OPT=-g -O0
OPT=-Oz

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

test: ${ALL_TT}


