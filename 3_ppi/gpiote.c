#include "gpiote.h"

// Not necessary to specify port, as default would be 0
// and all rows are on port 0 

void gpiote_init() {
    // Configures and clears GND pins on LED matrix
    gpio_init();

    // Channel 1
    GPIOTE->CONFIG[0] |= (BTN_A<<8); // Set pin 14 as pin to configure in PSEL
    GPIOTE->CONFIG[0] |= 1; // Set button as event
    GPIOTE->CONFIG[0] |= (2<<16); // Make event occur on falling edge 

    // Channel 2
    GPIOTE->CONFIG[1] |= (LED_ROW1<<8); // Set pin 21 as pin to configure in PSEL
    GPIOTE->CONFIG[1] |= 3; // Set LED as task
    GPIOTE->CONFIG[1] |= (3<<16); // Set LED to toggle
    GPIOTE->CONFIG[1] |= (1<<20); // Initialize value to be high (LED starts in on-mode)

    // Channel 3
    GPIOTE->CONFIG[2] |= (LED_ROW2<<8); // Set pin 22 as pin to configure in PSEL
    GPIOTE->CONFIG[2] |= 3; // Set LED as task
    GPIOTE->CONFIG[2] |= (3<<16); // Set LED to toggle
    GPIOTE->CONFIG[2] |= (1<<20); // Initialize value to be high (LED starts in on-mode)

    // Channel 4
    GPIOTE->CONFIG[3] |= (LED_ROW3<<8); // Set pin 15 as pin to configure in PSEL
    GPIOTE->CONFIG[3] |= 3; // Set LED as task
    GPIOTE->CONFIG[3] |= (3<<16); // Set LED to toggle
    GPIOTE->CONFIG[3] |= (1<<20); // Initialize value to be high (LED starts in on-mode)

    // Channel 5
    GPIOTE->CONFIG[4] |= (LED_ROW4<<8); // Set pin 24 as pin to configure in PSEL
    GPIOTE->CONFIG[4] |= 3; // Set LED as task
    GPIOTE->CONFIG[4] |= (3<<16); // Set LED to toggle
    GPIOTE->CONFIG[4] |= (1<<20); // Initialize value to be high (LED starts in on-mode)

    // Channel 6
    GPIOTE->CONFIG[5] |= (LED_ROW5<<8); // Set pin 19 as pin to configure in PSEL
    GPIOTE->CONFIG[5] |= 3; // Set LED as task
    GPIOTE->CONFIG[5] |= (3<<16); // Set LED to toggle
    GPIOTE->CONFIG[5] |= (1<<20); // Initialize value to be high (LED starts in on-mode)
}