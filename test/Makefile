ALL_LL=$(patsubst %.txt,%.ll,$(wildcard *.txt))
ALLOBJS=$(patsubst %.ll,%.o,${ALL_LL})
ALLASM=$(patsubst %.ll,%.s,${ALL_LL})
ALLBIN=$(patsubst %.ll,%,${ALL_LL})

ARDUINO=atmega328p

all: ${ALL_LL} ${ALLASM} ${ALLOBJS} ${ALLBIN}

clean:
	rm -f ${ALLBIN} ${ALLASM} ${ALLOBJS} ${ALL_LL} *.hex

%.ll : %.txt
	./robcmp $< > $@

%.o : %.ll
	echo "Building .o for $<"
	llc -march=avr -mcpu=${ARDUINO} $< -o $@ -filetype=obj

%.s : %.ll
	echo "Building .s for $<"
	llc -march=avr -mcpu=${ARDUINO} $< -o $@ -filetype=asm

% : %.o
	avr-gcc -mmcu=${ARDUINO} ../arduinowire/*.o $< -o $@
