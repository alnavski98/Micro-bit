#include "uart.h"

void uart_init() {
    // Choose RXD as input
    GPIO0->PIN_CNF[6] = 0;
    // Choose TXD as output
    GPIO1->PIN_CNF[8] = 1; 

    // No RTS or CTS line available
    UART->PSEL_RTS = ~0;
    UART->PSEL_CTS = ~0;

    // Selecting pin for RXD on port 0
    UART->PSEL_RXD = 6;

    // Selecting pin for TXD on port 1
    UART->PSEL_TXD = (1<<5);
    UART->PSEL_TXD |= 8;

    // Initializes baudrate = 9600, compensates for 
    // lack of flow control
    UART->BAUDRATE = 0x00275000;

    // Enabling uart
    UART->ENABLE = 4;

    // Start checking for incoming messages
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter) {
    // Start sending messages
    UART->TASKS_STARTTX = 1;

    // Writing letter (byte) to TXD register
    UART->TXD = letter;

    // Waits until byte has been transmitted
    while (!(UART->EVENTS_TXDRDY))
    {
        // Waiting
    }
    
    // Resets transmit ready event/flag 
    UART->EVENTS_TXDRDY = 0;


    UART->TASKS_STOPTX = 1;
}

char uart_read() {
    // Checks if message can be received
    if (UART->EVENTS_RXDRDY)
    {
        // Resets receive event/flag
        UART->EVENTS_RXDRDY = 0;

        // Reads what's stored in the RXD register
        return UART->RXD;
    }
    return '\0';
}