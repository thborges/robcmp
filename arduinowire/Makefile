CS = $(patsubst %.c,%.o,$(wildcard *.c))
SS = $(patsubst %.S,%.S.o,$(wildcard *.S))
CPPS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))

ARDUINO=atmega328p
#ARDUINO=atmega32u4

FLAGS=-Os -ffunction-sections -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR

all: core.a

core.a : $(CS) $(CPPS) $(SS)
	$(foreach obj, $(SS), avr-ar rcs $@ $(obj);)
	$(foreach obj, $(CS), avr-ar rcs $@ $(obj);)
	$(foreach obj, $(CPPS), avr-ar rcs $@ $(obj);)

%.S.o : %.S
	avr-gcc -c ${FLAGS} -mmcu=$(ARDUINO) $< -o $@

%.o : %.c
	avr-gcc -c ${FLAGS} -mmcu=$(ARDUINO) $<

%.o : %.cpp
	avr-g++ -c ${FLAGS} -mmcu=$(ARDUINO) $<

#clang -c --target=avr -mmcu=$(ARDUINO) -DF_CPU=16000000L -I/usr/avr/include $< -o $@
#clang -Iavr/include -c --target=avr -mmcu=$(ARDUINO) -DF_CPU=16000000L -I. $< -o $@


clean:
	rm -f *.d *.o *.a
