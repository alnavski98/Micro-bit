#include "gpiote.h"
#include "ppi.h"

int main() {

    gpiote_init();
    ppi_init();

    int sleep = 1000;
    while (1)
    {
        while (--sleep);
    }
    
    return 0;
}