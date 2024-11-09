ALL=$(patsubst %.rob,out/%,$(wildcard *.rob))
ALL_LL=$(patsubst %.rob,out/%.ll,$(wildcard *.rob))
ALL_TT=$(patsubst %.rob,%.tt,$(wildcard *.rob))
ALL_OO=$(patsubst %.rob,out/%.o,$(wildcard *.rob)) out/stm32f1.o

TOOL_OPEN_OCD_FOLDER=~/.platformio/packages/tool-openocd
ROBCMP=../../build/robcmp
INCLUDES=-I ../../lib

ifndef OPT
#OPT=-g -O0
OPT=-Oz
endif

LD_FLAGS=-nostdlib -entry=main -L../../lib -Tstm32f1.ld
LD_FLAGS+=-Bstatic 
LD_FLAGS+=--gc-sections
LD_FLAGS+=--lto=thin

DEPENDS=${ROBCMP} Makefile
LINK_DEPENDS=out/stm32f1.o

all: out test

out:
	mkdir -p out

out/stm32f1.o : ../../lib/stm32f1.rob ${DEPENDS}
	${ROBCMP} -a stm32f1 ${OPT} -o $@ $<

out/stm32f1.ll : ../../lib/stm32f1.rob ${DEPENDS}
	${ROBCMP} -a stm32f1 ${OPT} $< > $@

.SECONDARY:
out/%.o : %.rob out/stm32f1.o ${DEPENDS}
	${ROBCMP} -bdep -a stm32f1 ${OPT} ${INCLUDES} -o $@ $<

out/%.ll : %.rob ${DEPENDS}
	${ROBCMP} -bdep -a stm32f1 ${OPT} ${INCLUDES} $< > $@

%.tt : %.rob ${DEPENDS}
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

%.up : %.tt ${DEPENDS}
	${TOOL_OPEN_OCD_FOLDER}/bin/openocd -f ${TOOL_OPEN_OCD_FOLDER}/scripts/interface/stlink.cfg -f ${TOOL_OPEN_OCD_FOLDER}/scripts/target/stm32f1x.cfg -c "program $(patsubst %.tt,out/%,$<) reset exit"

out/% : out/%.o ${LINK_DEPENDS} 
	ld.lld ${LD_FLAGS} $^ -o $@

test: ${ALL_TT}

clean:
	@rm -f ${ALL} ${ALL_LL} ${ALL_OO}

