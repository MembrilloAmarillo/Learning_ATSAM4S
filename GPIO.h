#ifndef _GPIO_H_
#define _GPIO_H_

#include "def.h"

typedef enum { PA, PB, PC } PERIPHERALS;

typedef struct {
    volatile u32 PER;
    volatile u32 PDR;
    volatile u32 PSR;
    volatile u32 RESERVED0;
    volatile u32 OER;
    volatile u32 ODR;
    volatile u32 OSR;
    volatile u32 RESERVED1;
    volatile u32 IFER;
    volatile u32 IFDR;
    volatile u32 IFSR;
    volatile u32 RESERVED2;
    volatile u32 SODR;
    volatile u32 CODR;
    volatile u32 ODSR;
    volatile u32 PDSR;
    volatile u32 IER;
    volatile u32 IDR;
    volatile u32 IMR;
    volatile u32 ISR;
    volatile u32 MDER;
    volatile u32 MDDR;
    volatile u32 MDSR;
    volatile u32 RESERVED3;
    volatile u32 PUDR;
    volatile u32 PUER;
    volatile u32 PUSR;
    volatile u32 RESERVED4;
    volatile u32 ABCDSR1;
    volatile u32 ABCDSR2;
    volatile u32 RESERVED5[2];
    volatile u32 IFSCDR;
    volatile u32 IFSCER;
    volatile u32 IFSCSR;
    volatile u32 SCDR;
    volatile u32 PPDDR;
    volatile u32 PPDER;
    volatile u32 PPDSR;
    volatile u32 RESERVED6;
    volatile u32 OWER;
    volatile u32 OWDR;
    volatile u32 OWSR;
    volatile u32 RESERVED7;
    volatile u32 AIMER;
    volatile u32 AIMDR;
    volatile u32 AIMMR;
    volatile u32 RESERVED8;
    volatile u32 ESR;
    volatile u32 LSR;
    volatile u32 ELSR;
    volatile u32 RESERVED9;
    volatile u32 FELLSR;
    volatile u32 REHLSR;
    volatile u32 FRLHSR;
} Gpio_Register;

#define GPIOA ( ( Gpio_Register * ) 0x400E0E00 )
#define GPIOB ( ( Gpio_Register * ) 0x400E1000 ) 
#define GPIOC ( ( Gpio_Register * ) 0x400E1200 )

void enable_gpio ( Gpio_Register*, u32 );
void disable_gpio( Gpio_Register*, u32 );
int enable_peripheral_pin( Gpio_Register* gpio, u32 pin, u8 );

#endif