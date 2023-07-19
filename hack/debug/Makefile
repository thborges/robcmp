all:
	robcmp -a avr328p -O0 -g main.rob > main.ll
	robcmp -a avr328p -O0 -g main.rob -o main.o
	@#ld -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lSystem main.o -o main
	@#avr-ld --target avr5 -Tdata=0x800100 main.o -o main.elf
	avr-gcc -mmcu=atmega328p main.o -o main.elf

