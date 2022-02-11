#include "uart.h"
#include "def.h"

void enable_uart0()
{
    /* Mode register parity none */
    UART0_BASE->MR    = ( 4 << 9 );
    UART0_BASE->BRGR  = ( u16 )CLCK_DIVISOR;
    UART0_BASE->CR    = ( 1 << 6 ) | ( 1 << 4 );
}

#define NVIC_ISER ( ( volatile u32* ) 0xE000E100 )

void nvic_uart1_enable()
{
    *NVIC_ISER = ( 1 << 9 ); 
}

void interrupt_global_enable()
{
    __asm__( "cpsie if" );
}

void interrupt_global_disable()
{
    __asm__( "cpsid if" );
}

void enable_uart1()
{
    /* Mode register parity none */
    UART1_BASE->MR    = ( 4 << 9 );
    UART1_BASE->BRGR  = ( u16 )CLCK_DIVISOR;
    UART1_BASE->CR    = ( 1 << 6 ) | ( 1 << 4 );
    UART1_BASE->IER   = ( 1 << 0 );

    interrupt_global_enable();
    nvic_uart1_enable();
}


void uart1_interrupt()
{
    char c = UART1_BASE->RHR;
    // Print the char.
    while ((UART1_BASE->SR & (1 << 9)) == 0);
    UART1_BASE->THR = c;
}

void echo( Uart_Register* uart ) {
  while (1) {
    // Read the char.
    while ((uart->SR & (1 << 0)) == 0);
    char c = uart->RHR;

    // Print the char.
    while ((uart->SR & (1 << 9)) == 0);
    uart->THR = c;
  }
}

void print_char( u8 c, u8 target )
{
    switch( target )
    {
        case E_UART0:
        {
            while( ( UART0_BASE->SR & ( 1 << 9 ) ) == 0 );
            UART0_BASE->THR = c;
        } break;
        case E_UART1:
        {
            while( ( UART1_BASE->SR & ( 1 << 9 ) ) == 0 );
            UART1_BASE->THR = c;
        } break;
        default:
        {}
    }
}

void print_line( char* str, u8 target )
{
    while( *str != '\0' )
    {
        print_char( *str, target );
        str++;
    }
}