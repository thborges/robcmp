#include <stdint.h>

struct UCSRA {
    uint8_t MPCM0:1;
	uint8_t U2X0 :1;
	uint8_t UPE0 :1;
	uint8_t DOR0 :1;
	uint8_t FE0 :1;
	uint8_t UDRE0 :1;
	uint8_t TXC0 :1;
	uint8_t RXC0 :1;
};

/* USART0 control status register A */
volatile struct UCSRA *UCSR0A = (struct UCSRA*)0xc0;
volatile uint8_t *SREG = (uint8_t*)0x3f;
volatile uint16_t *STACK = (uint16_t*)0x3d;

void init() {
//	*SREG = 0;
	*STACK = 0x0AFF;
}

int main() {
	//init();
    UCSR0A->U2X0 = 1;
    //int a = UCSR0A->RXC0;
	return 10;
}
