CS = $(patsubst %.c,%.o,$(wildcard *.c))

ARDUINO=atmega328p
#ARDUINO=atmega32u4

all: $(CS)

%.o : %.c
	avr-gcc -c -Os -DF_CPU=16000000 -mmcu=$(ARDUINO) $<
	#clang -c --target=avr -mmcu=$(ARDUINO) -DF_CPU=16000000 -I/usr/avr/include $< -o $@
	#clang -D__ASSEMBLER__ -c --target=avr -mmcu=$(ARDUINO) -DF_CPU=16000000 -I. $< -o $@
	#clang -Iavr/include -c --target=avr -mmcu=$(ARDUINO) -DF_CPU=16000000 -I. $< -o $@


clean:
	rm -f *.d *.o
