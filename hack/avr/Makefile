INCLUDES=-I/Users/thborges/.platformio/packages/toolchain-atmelavr/avr/include
#AVRLIB=-L~/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/7.3.0/avr5 -lgcc
CC=clang
LLC=llc
CCPLAT=-target avr -mmcu=atmega328p -DF_CPU=16000000
ROBCMP=../../build/robcmp

AVRDUDECFG=-C /Users/thborges/.platformio/packages/tool-avrdude/avrdude.conf
AVRDUDEPORT=`ls /dev/cu.usb*`

ALL_C_ELF=$(patsubst %,%.hex,$(wildcard *.c))
ALL_ROB_ELF=$(patsubst %,%.hex,$(wildcard *.rob))
ALL=${ALL_C_ELF} ${ALL_ROB_ELF}

all: ${ROBCMP} ${ALL}

%.c.ll: %.c
	${CC} ${CCPLAT} -Oz -S -emit-llvm ${INCLUDES} $< -o $@

%.c.o: %.c
	${CC} ${CCPLAT} -ggdb -O0 -c ${INCLUDES} $< -o $@



%.rob.ll: %.rob
	${ROBCMP} -a avr328p -Oz $< > $@

%.rob.o: %.rob
	${ROBCMP} -a avr328p -Oz $< -o $@



%.s: %.ll
	${LLC} $< -o $@ -filetype=asm

%.elf : %.o
	@#${CC} -v ${CCPLAT} ${AVRLIB} $< -o $@
	@#avr-gcc -v -mmcu=atmega328p $< -o $@
	#avr-ld -o $@ -Tdata=0x800100 $<
	ld.lld -o $@ -Tdata=0x800100 $<


%.hex : %.elf
	#avr-objcopy -Oihex $< $@
	llvm-objcopy -Oihex $< $@

%.up: %.hex
	avrdude ${AVRDUDECFG} -v -V -c arduino -p m328p -U flash:w:$<:i -P ${AVRDUDEPORT}

clean:
	rm -f *.s *.o *.elf *.ll *.hex
