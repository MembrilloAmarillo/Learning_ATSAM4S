#ifndef _UART_H_
#define _UART_H_

#include "def.h"

typedef struct
{
	u32 CR;
	u32 MR;
	u32 IER;
	u32 IDR;
	u32 IMR;
	u32 SR;
	u32 RHR;
	u32 THR;
	u32 BRGR;
} uart_register;

#define UART0_BASE ( ( volatile uart_register * ) 0x400E0600 )
#define UART1_BASE ( ( volatile uart_register * ) 0x400E0800 )

#define DEFAULT_PERIPHERAL_CLOCK 4000000 // 4MHz
#define CLCK_DIVISOR ( DEFAULT_PERIPHERAL_CLOCK / ( 16 * 9600 ) )

void enable_uart0();
void enable_uart1();
void print_char( u8, u8 );

#endif