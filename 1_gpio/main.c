#include <stdint.h>
#include <stdio.h>

#define GPIO0 ((NRF_GPIO_REGS0*)0x50000000) //gpio 0 base adress
#define GPIO1 ((NRF_GPIO_REGS1*)0x50000300) //gpio 1 base adress

/*
	Knapp A og B:
	- Koblet til P0.14 og P0.23 henholdsvis på nRF52833'en
	- Pinnene vil være lave dersom knappene trykkes inn (aktivt lav)

	Datablad nRF52833:
	- Kode okkuperer ...
	- Baseadresser til GPIO-modulene:
		- GPIO P0: 0x50000000
		- GPIO P1: 0x50000300
*/


typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1_0[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS0;

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1_1[118];
	volatile uint32_t PIN_CNF[10];
} NRF_GPIO_REGS1;


// Sjekker om knapp A er trykket inn
int ubit_button_press_a(){
	return (!(GPIO0->IN & (1 << 14)));
}

// Tilsvarende for knapp B
int ubit_button_press_b(){
	return (!(GPIO0->IN & (1 << 23)));
}

int main(){

	// Configure leds (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	GPIO0->PIN_CNF[21] = 1; //Row 1
	GPIO0->PIN_CNF[22] = 1; //Row 2
	GPIO0->PIN_CNF[15] = 1; //Row 3
	GPIO0->PIN_CNF[24] = 1; //Row 4
	GPIO0->PIN_CNF[19] = 1; //Row 5

	GPIO0->PIN_CNF[28] = 1; //Col 1
	GPIO0->PIN_CNF[11] = 1; //Col 2
	GPIO0->PIN_CNF[31] = 1; //Col 3
	GPIO1->PIN_CNF[5] = 1;  //Col 4
	GPIO0->PIN_CNF[30] = 1; //Col 5 
	
	// Configure buttons (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	GPIO0->PIN_CNF[14] = 0; // button A 
	GPIO0->PIN_CNF[23] = 0; // button B

	// Clearer radene
	GPIO0->OUTCLR = (1 << 21);
	GPIO0->OUTCLR = (1 << 22);
	GPIO0->OUTCLR = (1 << 15);
	GPIO0->OUTCLR = (1 << 24);
	GPIO0->OUTCLR = (1 << 19);

	// Setter kolonnene
	GPIO0->OUTSET = (1 << 28);
	GPIO0->OUTSET = (1 << 11);
	GPIO0->OUTSET = (1 << 31);
	GPIO1->OUTSET = (1 << 5);
	GPIO0->OUTSET = (1 << 30);

	int sleep = 0;
	while(1){
		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if (ubit_button_press_b())
		{
			// For å teste om en enkelt LED lyser
			//GPIO0->OUTSET = (1 << 24);
			//GPIO0->OUTCLR = (1 << 28);
			
			GPIO0->OUT |= (1 << 21) | (1 << 22) | (1 << 15) | (1 << 24) | (1 << 19);
			GPIO0->OUT &= ~(1 << 28) & ~(1 << 11) & ~(1 << 31) &  ~(1 << 30);
			GPIO1->OUT &= ~(1 << 5);
		}
		
		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if (ubit_button_press_a())
		{
			//GPIO0->OUTCLR = (1 << 24);
			//GPIO0->OUTSET = (1 << 28);

			GPIO0->OUT &= ~(1 << 21) & ~(1 << 22) & ~(1 << 15) & ~(1 << 24) & ~(1 << 19);
			GPIO0->OUT |= (1 << 28) | (1 << 11) | (1 << 31) | (1 << 30);
			GPIO1->OUT |= (1 << 5);

		}
		
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
