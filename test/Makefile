ALL_LL=$(patsubst %.txt,out/%.ll,$(wildcard *.txt))
ALLOBJS=$(patsubst %.ll,%.o,${ALL_LL})
ALLASM=$(patsubst %.ll,%.s,${ALL_LL})
ALLBIN=$(patsubst %.ll,%,${ALL_LL})
ARDUINO_OBJ=$(wildcard ../arduinowire/*.o) $(wildcard ../arduinowire/*.S)

ARDUINO=atmega328p
#ARDUINO=atmega32u4

COMPILER_NAME=$(shell basename $(shell dirname "${PWD}"))

all: ${ALL_LL} ${ALLASM} ${ALLOBJS} ${ALLBIN}

clean:
	rm -f ${ALLBIN} ${ALLASM} ${ALLOBJS} ${ALL_LL} out/*.hex

out/%.ll : %.txt ${COMPILER_NAME}
	./${COMPILER_NAME} $< > $@

%.o : %.ll
	llc -march=avr -mcpu=${ARDUINO} $< -o $@ -filetype=obj

%.s : %.ll
	llc -march=avr -mcpu=${ARDUINO} $< -o $@ -filetype=asm

#% : %.o ../arduinowire/core.a
#	avr-gcc -mmcu=${ARDUINO} $< ../arduinowire/core.a -o $@

% : %.s out/core.a
	avr-gcc -flto -Os -mmcu=${ARDUINO} $< out/core.a -o $@

#% : %.o out/core.a
#	clang --target=avr -mmcu=${ARDUINO} $< out/core.a -o $@

