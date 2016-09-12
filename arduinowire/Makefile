CS = $(patsubst %.c,%.o,$(wildcard *.c))

all: $(CS)

%.o : %.c
	avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega328p -c $<
#	avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega32u4 -c $<

clean:
	rm *.o
