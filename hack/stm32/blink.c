
// CLOCK GATES FOR IO
#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))

// PORTC is enabled by IOPCEN, the bit four in RCC_APB2ENR
#define RCC_APB2ENR_IOPCEN (1 << 4)

// GPIO PORTC base address
#define GPIO_PORTC_BASE 0x40011000

enum PIN_MODE {INPUT, OUTPUT10MHz, OUTPUT2MHz, OUTPUT50MHz};
enum INPUT_MODE {ANALOG, FLOATING, PULLUPDOWN};
enum OUTPUT_MODE {PUSHPULL, OPENDRAIN, APUSH_PULL, AOPENDRAIN};

struct GPIOx_CRH {
	unsigned MODE8  : 2;
	unsigned CNF8   : 2;
	unsigned MODE9  : 2;
	unsigned CNF9   : 2;
	unsigned MODE10 : 2;
	unsigned CNF10  : 2;
	unsigned MODE11 : 2;
	unsigned CNF11  : 2;
	unsigned MODE12 : 2;
	unsigned CNF12  : 2;
	unsigned MODE13 : 2;
	unsigned CNF13  : 2;
	unsigned MODE14 : 2;
	unsigned CNF14  : 2;
	unsigned MODE15 : 2;
	unsigned CNF15  : 2;
};

struct GPIOx_ODR {
	unsigned PIN0  : 1;
	unsigned PIN1  : 1;
	unsigned PIN2  : 1;
	unsigned PIN3  : 1;
	unsigned PIN4  : 1;
	unsigned PIN5  : 1;
	unsigned PIN6  : 1;
	unsigned PIN7  : 1;
	unsigned PIN8  : 1;
	unsigned PIN9  : 1;
	unsigned PIN10 : 1;
	unsigned PIN11 : 1;
	unsigned PIN12 : 1;
	unsigned PIN13 : 1;
	unsigned PIN14 : 1;
	unsigned PIN15 : 1;
	unsigned __reserved : 16;
};

#define GPIOC_CRH (*(volatile struct GPIOx_CRH *)(GPIO_PORTC_BASE + 0x4))
#define GPIOC_ODR (*(volatile struct GPIOx_ODR *)(GPIO_PORTC_BASE + 0xC))

void wait() {
	volatile int i = 100000;
	while(i > 0) {
		i--;
	}
}
int main() {
	// Enable port C clock gate.
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

	// PORT C, PIN 13 as output
	GPIOC_CRH.MODE13 = OUTPUT50MHz;
	GPIOC_CRH.CNF13 = PUSHPULL;
	
	for(;;) {
		GPIOC_ODR.PIN13 = 0;
		wait();
		GPIOC_ODR.PIN13 = 1;
		wait();
	}

	return 0;
}

