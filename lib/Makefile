
all: avr5.o

avr5.o: avr5.s
	@#here we are interested in the fastest possible code, intead of size
	avr-gcc -mmcu=avr5 -O3 -c avr5.S


clean:
	rm -f avr5.o
