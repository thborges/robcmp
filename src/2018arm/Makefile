ARDUINO=10805
F_CPU=16000000L
MCU=atmega328p

INCLUDES= \
	-I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino \
	-I/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/eightanaloginputs

ARGS=-Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR

CPPS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: lib.a

lib.a: ${CPPS}
	$(foreach obj, $(CPPS), avr-ar rcs $@ $(obj);)

%.o: %.cpp
	avr-g++ ${ARGS} ${INCLUDES} -DF_CPU=${F_CPU} -DARDUINO=${ARDUINO} -mmcu=${MCU} -c $< -o $@

clean:
	rm *.o
	rm *.d
