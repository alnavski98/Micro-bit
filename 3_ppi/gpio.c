#include "gpio.h"

void gpio_init() {
    // Setting direction of led GND pins on port 0 as output
    GPIO0->DIRSET |= (1<<28) | (1<<11) | (1<<31) | (1<<30);
    // Equivalently for port 1 led GND pins
    GPIO1->DIRSET |= (1<<5);

    // Clearing the same port 0 and 1 pins
    GPIO0->OUTCLR |= (1<<28) | (1<<11) | (1<<31) | (1<<30);
    GPIO1->OUTCLR |= (1<<5);
}