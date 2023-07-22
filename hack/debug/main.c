
typedef struct {
	char pin8 : 1;
	char pin9 : 1;
	char pin10 : 1;
	char pin11 : 1;
	char pin12 : 1;
	char pin13 : 1;
	char others : 2;
} ddrb_t;


typedef struct {
	char pin8 : 1;
	char pin9 : 1;
	char pin10 : 1;
	char pin11 : 1;
	char pin12 : 1;
	char pin13 : 1;
	char others : 2;
} portb_t;


void wait(long qtd) {
	volatile long q = qtd;
	while(q > 0) {
		q--;
	}
}

int main() {
	volatile ddrb_t *ddrb = (ddrb_t*)0x24;
	volatile portb_t *portb = (portb_t*)0x25;

	char a = ddrb->pin13;

	ddrb->pin13 = 1; //output
	char i = 10;
	for(;;) {
		// blink
		portb->pin13 = 0;
		wait(i*100000);
		portb->pin13 = 1;
		wait(i*100000);
		
		i--;
		if (i == 0) {
			i = 10;
		}
	}
}

