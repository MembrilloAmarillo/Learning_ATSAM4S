#ifndef _PMC_H_
#define _PMC_H_

#include "def.h"

typedef struct 
{
	volatile u32 SCER;
	volatile u32 SCDR;
	volatile u32 SCSR;
	volatile u32 reserved0;
	volatile u32 PCER0;
	volatile u32 PCDR0;
	volatile u32 PCSR0;
	volatile u32 reserved1;
	volatile u32 CKGR_MOR;
	volatile u32 CKGR_MCFR;
	volatile u32 CKGR_PLLAR;
	volatile u32 CKGR_PLLBR;
	volatile u32 MCKR;
	volatile u32 reserved2;
	volatile u32 USB;
	volatile u32 reserved3;
	volatile u32 PCK0;
	volatile u32 PCK1;
	volatile u32 PCK2;
	volatile u32 reserved4;
	volatile u32 reserved5;
	volatile u32 reserved6;
	volatile u32 reserved7;
	volatile u32 reserved8;
	volatile u32 reserved9;
	volatile u32 IER;
	volatile u32 IDR;
	volatile u32 SR;
	volatile u32 IMR;
	volatile u32 FSMR;
	volatile u32 FSPR;
	volatile u32 FOCR;
	volatile u32 reserved10[25];
	volatile u32 WPMR;
	volatile u32 WPSR;
	volatile u32 reserved11[4];
	volatile u32 PCER1;
	volatile u32 PCDR1;
	volatile u32 PCSR1;
	volatile u32 OCR;
} Pmc_Register;

#define PMC_BASE ( ( Pmc_Register * ) 0x400E0400 )

void enable_main_clock();
void enable_peripheral_clock( int );

#endif