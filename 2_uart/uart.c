#include "uart.h"

// Skrives det til riktig register når jeg velger pinne for TXD?
// Er det nødvendig 
// Hvorfor settes PSEL_RXD og PSEL_TXD registrene slik det gjøres
void uart_init() {
    // Choose RXD as input
    GPIO0->PIN_CNF[6] = 0;
    // Choose TXD as output
    GPIO1->PIN_CNF[8] = 1; 

    // No RTS or CTS line available
    UART->PSEL_RTS = ~0;
    UART->PSEL_CTS = ~0;

    // Selecting pin for RXD on port 0
    //UART->PSEL_RXD = 6;
    UART->PSEL_RXD = 0x28; // Equivalent to |= 8 | (1<<5) 

    // Selecting pin for TXD on port 1
    //UART->PSEL_TXD = (1<<5);    //0b0000000000000000000000000100000
    //UART->PSEL_TXD |= 8;        //0b0000000000000000000000000101000 
    UART->PSEL_TXD = 0x06; //Equivalent to = 6

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

    // Stop sending messages
    UART->TASKS_STOPTX = 1;
}

char uart_read() {
    // To avoid package loss
    //UART->EVENTS_RXDRDY = 0;

    // Checks if message can be received
    if (UART->EVENTS_RXDRDY)
    {
        // Resets receive event/flag
        UART->EVENTS_RXDRDY = 0;

        // Reads what's stored in the RXD register
        return UART->RXD;
    }

    // Return nothing if no message is received
    return '\0';
}

void uart_send_str(char **str) {
    // Start sending messages
    UART->TASKS_STARTTX = 1;

    // Stores address of (first) pointer
    char *letter_ptr = *str;
    while (*letter_ptr != '\0')
    {
        // Stores value in TXD register
        UART->TXD = *letter_ptr;

        // Waits until value has been sent
        while (!UART->EVENTS_TXDRDY);
        UART->EVENTS_TXDRDY = 0;

        // Moves to the next value address
        letter_ptr++;
    }
}