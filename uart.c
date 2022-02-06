#include "uart.h"
#include "def.h"

void enable_uart0()
{
    /* Mode register parity none */
    UART0_BASE->MR    = ( 4 << 9 );
    UART0_BASE->BRGR  = ( u16 )CLCK_DIVISOR;
    UART0_BASE->CR   |= ( 1 << 6 );
}

void enable_uart1()
{
    /* Mode register parity none */
    UART1_BASE->MR    = ( 4 << 9 );
    UART1_BASE->BRGR  = ( u16 )CLCK_DIVISOR;
    UART1_BASE->CR   |= ( 1 << 6 );
}

void print_char( u8 c, u8 target )
{
    switch( target )
    {
        case 0:
        {
            while( ( UART0_BASE->SR & ( 1 << 9 ) ) == 0 );
            UART0_BASE->THR = c;
        } break;
        case 1:
        {
            while( ( UART1_BASE->SR & ( 1 << 9 ) ) == 0 );
            UART1_BASE->THR = c;
        } break;
        default:
        {}
    }
}