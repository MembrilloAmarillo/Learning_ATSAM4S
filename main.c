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
    enable_peripheral_clock(9); // Enable peripheral id 9 = uart1

    // UART1, TX pin 3 of GPIO B, Peripheral A
    // Enable PB3 -> UTXD1
    // Enables peripheral control of the pin
    enable_peripheral_pin( GPIOB, 3, PA );
    enable_peripheral_pin( GPIOB, 2, PA );

    // We can make this function more general, but I dont think
    // it is necessary for now
    // Enable uart interrupts before making RX
    enable_uart0();
    enable_uart1();

    while (1) {
        GPIOC->CODR = 1 << 23;
        GPIOA->CODR = 1 << 18;
        //print_line( "henlo\n", E_UART1 );
        delay();
        GPIOC->SODR = 1 << 23;
        GPIOA->SODR = 1 << 18;
        delay();
    }
}