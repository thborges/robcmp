ALL_LL=$(patsubst %.txt,out/%.ll,$(wildcard *.txt))
ALLOBJS=$(patsubst %.ll,%.o,${ALL_LL})
ALLASM=$(patsubst %.ll,%.s,${ALL_LL})
ALLBIN=$(patsubst %.ll,%,${ALL_LL})
ARDUINO_OBJ=$(wildcard ../arduinowire/*.o)

ARDUINO=atmega328p
#ARDUINO=atmega32u4

all: ${ALL_LL} ${ALLASM} ${ALLOBJS} ${ALLBIN}

clean:
	rm -f ${ALLBIN} ${ALLASM} ${ALLOBJS} ${ALL_LL} out/*.hex out/core.a

out/%.ll : %.txt
	./robcmp $< > $@

%.o : %.ll
	llc -march=avr -mcpu=${ARDUINO} $< -o $@ -filetype=obj

%.s : %.ll
	llc -march=avr -mcpu=${ARDUINO} $< -o $@ -filetype=asm

out/core.a : $(ARDUINO_OBJS)
	$(foreach obj, $(ARDUINO_OBJ), avr-ar rcs $@ $(obj);)

% : %.o out/core.a
	avr-gcc -mmcu=${ARDUINO} $< out/core.a -o $@
