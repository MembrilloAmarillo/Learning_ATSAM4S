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
    enable_gpio( GPIOC, 23 );
    enable_gpio( GPIOA, 18 );

    //enable_main_clock();
    enable_peripheral_clock(9);

    // UART1, TX pin 3 of GPIO B, Peripheral A
    // Enable PB3 -> UTXD1
    // Enables peripheral control of the pin
    int enable_ok = enable_peripheral_pin( GPIOB, 3, PA );
    int ok_print = 1;
    if( enable_ok == 0 ) ok_print = 0;

    // We can make this function more general, but I dont think
    // it is necessary for now
    enable_uart0();
    enable_uart1();

    while (1) {
        GPIOC->CODR = 1 << 23;  // Set and clear registers must be written ( do not use |= )
        GPIOA->CODR = 1 << 18;
        if( ok_print == 1 )
        {
            print_char( 'a', E_UART1 );
        }
        delay();
        GPIOC->SODR = 1 << 23;
        GPIOA->SODR = 1 << 18;
        delay();
    }
}