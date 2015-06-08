ALLTESTS=$(patsubst %.txt,%.ll,$(wildcard *.txt))
ALLOBJS=$(patsubst %.ll,%.o,${ALLTESTS})
ALLASM=$(patsubst %.ll,%.s,${ALLTESTS})
ALLBIN=$(patsubst %.ll,%,${ALLTESTS})

ARDUINO=atmega328p

all: ${ALLTESTS} ${ALLASM} ${ALLOBJS} ${ALLBIN}

clean:
	rm -f *.ll
	rm -f *.s
	rm -f *.o

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
