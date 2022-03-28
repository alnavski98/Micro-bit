#include <stdio.h>
#include "gpio.h"
#include "uart.h"

#define button_A_pin 14
#define button_B_pin 23

/*
    Remember that the buttons are active low so to check for button press
    if-statements need to register when low signal is activated
*/

int main() {
    gpio_init();
    uart_init();

    int sleep = 0;
    while (1)
    {

        // Check for button A press
        if (!(GPIO0->IN & (1<<button_A_pin)))
        {
            uart_send('A');
        }

        // Equivalen for button B
        if (!(GPIO0->IN & (1<<button_B_pin)))
        {
            uart_send('B');
        }
        
        // Checks if a letter is read
        if (uart_read())
        {
            // Turns off LED's if one row is lit
            if ((GPIO0->OUT) & (1<<21))
            {
                //GPIO0->OUT &= ~(1<<21) & ~(1<<22) & ~(1<<15) & ~(1<<24) & ~(1<<19);
                gpio_lights_off();
            }            
            else
            {
                //GPIO0->OUT |= (1<<21) | (1<<22) | (1<<15) | (1<<24) | (1<<19);
                gpio_lights_on();
            }
        }
        sleep = 1000;
        while (--sleep);
    }
    
    return 0;
}

ssize_t _write(int fd, const void *buf, size_t count) {
    char *letter = (char *)(buf);
    for (int i = 0; i < count; i++)
    {
        uart_send(*letter);
        letter++;
    }
    return count;
}