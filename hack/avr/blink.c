#include <avr/io.h>

void wait() {
	volatile int32_t i = 100000;
	while (i > 0) {
		i--;
	}
}

int main() {

	// pin 13 as output
	DDRB |= _BV(DDB5);

	while (1) {
		PORTB |= _BV(PORTB5);
		wait();
		PORTB &= ~(_BV(PORTB5));
		wait();
	}

}

