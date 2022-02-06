/*
Author: MembrilloAmarillo
LICENSE: MIT 

Learning ATSAM4S32C
*/

#include <stdint.h>

#include "GPIO.h"
#include "def.h"
#include "PMC.h"
#include "uart.h"

// Ultra temporary static delay. I have to learn about this
void delay()
{
    for (u32 i = 0; i < 250000; i++)
    {
        __asm__("nop");
    }
}

void main( void )
{ 
    GPIOC->OER     = 1 << 23;
    GPIOA->OER     = 1 << 18;

    //enable_main_clock();
    enable_peripheral_clock(9);

    // UART1, TX pin 3 of GPIO B
    GPIOB->ABCDSR1 = 0 << 3;
    GPIOB->ABCDSR2 = 0 << 3; // Enable PB3 -> UTXD1
    GPIOB->PDR     = 1 << 3; // Enables peripheral control of the pin

    // If set to 1, the peripheral is inactive, so we wait until
    // is set to 0
    while( ( GPIOA->PSR & ( 1 << 10 ) ) == 1 );

    // We can make this function more general, but I dont think
    // it is necessary for now
    enable_uart0();
    enable_uart1();

    while (1) {
        GPIOC->CODR = 1 << 23;  // Set and clear registers must be written ( do not use |= )
        GPIOA->CODR = 1 << 18;
        print_char( 'a', 1 );
        delay();
        GPIOC->SODR = 1 << 23;
        GPIOA->SODR = 1 << 18;
        delay();
    }
}