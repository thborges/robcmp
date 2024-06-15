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

all: out test

out:
	mkdir -p out

clean:
	@rm -f ${ALL} ${ALL_LL} ${ALL_OO}

.SECONDARY:
out/%.o : %.rob ${ROBCMP} Makefile
	@touch temp.spec && truncate -s 0 temp.spec
	@[ -f $(patsubst %.rob,%.spec,$<) ] && cp $(patsubst %.rob,%.spec,$<) temp.spec || true
	${ROBCMP} ${OPT} -I ../../lib -bdep -s temp.spec -o $@ $<

out/%.ll : %.rob ${ROBCMP} Makefile
	@touch temp.spec && truncate -s 0 temp.spec
	@[ -f $(patsubst %.rob,%.spec,$<) ] && cp $(patsubst %.rob,%.spec,$<) temp.spec || true
	${ROBCMP} ${OPT} -I ../../lib -bdep -s temp.spec $< > $@

%.tt : %.rob
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

% : %.o
ifeq ($(OS), Msys)
	${LD} -e __main $< -o $@
else ifeq ($(OS), Darwin)
	${CC} -Wl,-dead_strip $< -o $@
else
	${CC} -Wl,--gc-sections -no-pie $< -o $@
endif

test: ${ALL_TT}


