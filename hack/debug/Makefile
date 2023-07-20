AVRDUDECFG=-C /Users/thborges/.platformio/packages/tool-avrdude/avrdude.conf
AVRDUDEPORT=`ls /dev/cu.usb*`

#OPT=-O0 -g
OPT=-Os

all: avr5.o main.o main.lld.elf main.lld.size main.avr.elf main.avr.size

avr5.o: avr5.s
	avr-gcc -mmcu=atmega328p -O3 -c avr5.S

main.ll: main.rob
	robcmp -a avr328p ${OPT} $< > $@

main.o: main.rob
	robcmp -a avr328p ${OPT} $< -o $@
	@#ld -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem main.o -o main

main.c.o: main.c
	avr-gcc ${OPT} -mmcu=atmega328p -c $< -o $@

main.avr.elf: main.c.o
	avr-gcc -Wl,--gc-sections ${OPT} -mmcu=atmega328p $< -o $@

main.lld.elf: main.o avr5.o
	@#clang-16 -v -fuse-ld=lld -e main -target avr -mmcu=atmega328p main.o -o main.elf
	ld.lld --gc-sections -o $@ -Tavr5.ld -Tdata=0x800100 -e main ${LOPT} main.o avr5.o

%.hex : %.elf
	avr-objcopy -Oihex $< $@

%.up: %.hex
	avrdude ${AVRDUDECFG} -v -V -c arduino -p m328p -U flash:w:$<:i -P ${AVRDUDEPORT}

%.size: %.elf
	avr-size $<

clean:
	rm -f *.o *.elf *.ll *.hex
