#ifndef _GPIO_H_
#define _GPIO_H_

#include "def.h"

typedef enum { PA, PB, PC } PERIPHERALS;

typedef struct {
    u32 PER;
    u32 PDR;
    u32 PSR;
    u32 RESERVED0;
    u32 OER;
    u32 ODR;
    u32 OSR;
    u32 RESERVED1;
    u32 IFER;
    u32 IFDR;
    u32 IFSR;
    u32 RESERVED2;
    u32 SODR;
    u32 CODR;
    u32 ODSR;
    u32 PDSR;
    u32 IER;
    u32 IDR;
    u32 IMR;
    u32 ISR;
    u32 MDER;
    u32 MDDR;
    u32 MDSR;
    u32 RESERVED3;
    u32 PUDR;
    u32 PUER;
    u32 PUSR;
    u32 RESERVED4;
    u32 ABCDSR1;
    u32 ABCDSR2;
    u32 RESERVED5[2];
    u32 IFSCDR;
    u32 IFSCER;
    u32 IFSCSR;
    u32 SCDR;
    u32 PPDDR;
    u32 PPDER;
    u32 PPDSR;
    u32 RESERVED6;
    u32 OWER;
    u32 OWDR;
    u32 OWSR;
    u32 RESERVED7;
    u32 AIMER;
    u32 AIMDR;
    u32 AIMMR;
    u32 RESERVED8;
    u32 ESR;
    u32 LSR;
    u32 ELSR;
    u32 RESERVED9;
    u32 FELLSR;
    u32 REHLSR;
    u32 FRLHSR;
} gpio_register;

#define GPIOA ( ( volatile gpio_register * ) 0x400E0E00 )
#define GPIOB ( ( volatile gpio_register * ) 0x400E1000 ) 
#define GPIOC ( ( volatile gpio_register * ) 0x400E1200 )

void enable_gpio( volatile gpio_register*, u32 );
void disable_gpio( volatile gpio_register*, u32 );
int enable_peripheral_pin( volatile gpio_register* gpio, u32 pin, u8 );

#endif