
GEN=avr5.o avr51.o

all: ${GEN}

avr5.o: avr5.S
	@#here we are interested in the fastest possible code, intead of size
	@#avr-gcc -mmcu=avr5 -O3 -c $<
	clang --target=avr -mmcu=avr5 -O3 -c $<

avr51.o: avr51.S
	@#here we are interested in the fastest possible code, intead of size
	@#avr-gcc -mmcu=avr5 -O3 -c $<
	clang --target=avr -mmcu=avr51 -O3 -c $<

clean:
	rm -f ${GEN}
