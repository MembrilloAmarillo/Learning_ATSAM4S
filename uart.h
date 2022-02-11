#ifndef _UART_H_
#define _UART_H_

#include "def.h"

typedef struct
{
	volatile u32 CR;
	volatile u32 MR;
	volatile u32 IER;
	volatile u32 IDR;
	volatile u32 IMR;
	volatile u32 SR;
	volatile u32 RHR;
	volatile u32 THR;
	volatile u32 BRGR;
} Uart_Register;

typedef enum { E_UART0, E_UART1 } e_uart;

#define UART0_BASE ( ( Uart_Register * ) 0x400E0600 )
#define UART1_BASE ( ( Uart_Register * ) 0x400E0800 )

#define DEFAULT_PERIPHERAL_CLOCK 4000000 // 4MHz
#define CLCK_DIVISOR ( DEFAULT_PERIPHERAL_CLOCK / ( 16 * 9600 ) )

void enable_uart0();
void enable_uart1();
void print_char( u8, u8 );
void print_line( char*, u8 );
void echo( Uart_Register* );

#endif