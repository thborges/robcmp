
GEN=avr5.o avr51.o cortex-m3-arm-missing.o cortex-m0plus-arm-missing.o

all: ${GEN}

avr5.o: avr5.S
	@#here we are interested in the fastest possible code, intead of size
	@#avr-gcc -mmcu=avr5 -O3 -c $<
	clang --target=avr -mmcu=avr5 -O3 -c $<

avr51.o: avr51.S
	@#here we are interested in the fastest possible code, intead of size
	@#avr-gcc -mmcu=avr5 -O3 -c $<
	clang --target=avr -mmcu=avr51 -O3 -c $<

cortex-m3-arm-missing.o: arm-missing.c
	clang --target=arm-none-eabi -mcpu=cortex-m3 -mthumb -O3 -c $< -o $@

cortex-m0plus-arm-missing.o: arm-missing.c
	clang --target=arm-none-eabi -mcpu=cortex-m0plus -mthumb -O3 -c $< -o $@

clean:
	rm -f ${GEN}
