CC=~/.platformio/packages/toolchain-gccarmnoneeabi/bin/arm-none-eabi-gcc
#CC=/usr/local/opt/llvm/bin/clang
LLC=/usr/local/opt/llvm/bin/llc
OBJCOPY=/usr/local/opt/llvm/bin/llvm-objcopy
INCLUDES=
#CCPLAT=-target arm-none-eabi -mcpu=cortex-m3 -mthumb
CCPLAT=-mcpu=cortex-m3 -mthumb
ROBCMP=../../build/robcmp

USBPORT=`ls /dev/cu.usb*`

ALL_C=$(patsubst %,%.bin,$(wildcard *.c))
ALL_ROB=$(patsubst %,%.bin,$(wildcard *.rob))
ALL=${ALL_C} ${ALL_ROB}

all: ${ROBCMP} ${ALL}

%.c.ll: %.c
	#${CC} ${CCPLAT} -Oz -S -emit-llvm ${INCLUDES} $< -o $@
	${CC} ${CCPLAT} -Os -S -emit-llvm ${INCLUDES} $< -o $@

%.c.o: %.c
	${CC} -v ${CCPLAT} -Os -c ${INCLUDES} $< -o $@



%.rob.ll: %.rob
	${ROBCMP} -a stm32f1 -Oz $< > $@

%.rob.o: %.rob
	${ROBCMP} -a stm32f1 -Oz $< -o $@



%.s: %.ll
	${LLC} $< -o $@ -filetype=asm

%.elf : %.o
	#${CC} ${CCPLAT} -nostdlib -Wl,-entry=main -Wl,-Tmemory.lld.ld $< -o $@
	${CC} -mthumb -mcpu=cortex-m3 -nostdlib -Wl,-Tmemory.gcc.ld $< -o $@


%.bin : %.elf
	${OBJCOPY} -Oihex $< $@

%.up: %.bin
	./stm32flash -w $< -v -g 0x0 ${USBPORT}

clean:
	rm -f *.s *.o *.elf *.ll *.bin
