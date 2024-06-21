
GEN=avr5.o

all: ${GEN}

avr5.o: avr5.S
	@#here we are interested in the fastest possible code, intead of size
	avr-gcc -mmcu=avr5 -O3 -c $<

clean:
	rm -f ${GEN}
