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

LD_FLAGS=-nostdlib -entry=main -L../../lib -Tarch/rp/rp2040/rp2040.ld
LD_FLAGS+=-Bstatic 
LD_FLAGS+=--gc-sections
LD_FLAGS+=--lto=thin

DEPENDS=${ROBCMP} Makefile
LINK_DEPENDS=out/init.o ../../lib/arch/rp/rp2040/boot2.o ../../lib/arm-none-eabi-thumb-v6m-libgcc.a ../../lib/cortex-m0plus-arm-missing.o
#../../lib/libclang_rt.builtins-armv6.a

all: out test

out:
	mkdir -p out

out/init.o : ../../lib/arch/rp/rp2040/init.rob ${DEPENDS}
	${ROBCMP} -a rp2040 ${OPT} -o $@ $<

out/init.ll : ../../lib/arch/rp/rp2040/init.rob ${DEPENDS}
	${ROBCMP} -a stm32f1 ${OPT} $< > $@

out/%.o : %.rob out/init.o ${DEPENDS}
	${ROBCMP} -bdep -a rp2040 ${OPT} ${INCLUDES} -o $@ $<

out/%.ll : %.rob ${DEPENDS}
	${ROBCMP} -bdep -a rp2040 ${OPT} ${INCLUDES} $< > $@

%.tt : %.rob ${DEPENDS}
	@-./runtest.sh $< $(patsubst %.rob,out/%,$<) 

out/%.uf2 : out/%
	llvm-size $<
	./elf2uf2/elf2uf2 -v $< $@

out/% : out/%.o ${LINK_DEPENDS} 
	ld.lld ${LD_FLAGS} $^ -o $@

%.up : out/%.uf2
	cp $< /Volumes/RPI-RP2

test: ${ALL_TT}

clean:
	@rm -f ${ALL} ${ALL_LL} ${ALL_OO}
	@rm out/*

