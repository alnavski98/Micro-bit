#include "gpio.h"
#include "uart.h"

#define button_A_pin 14
#define button_B_pin 23

/*
    Remember that the buttons are active low so to check for button press
    if-statements need to register when low signal is activated
*/

int main() {
    uart_init();

    while (1)
    {
        // If A-button is pressed send 'A'
        // Likewise for B-button

        // Check for button A press
        if (!(GPIO0->IN & (1<<button_A_pin)))
        {
            uart_send('A');
        }
        if (!(GPIO0->IN & (1<<button_B_pin)))
        {
            uart_send('B');
        }
        
        
    }
    
    
    return 0;
}