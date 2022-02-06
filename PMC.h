#ifndef _PMC_H_
#define _PMC_H_

#include "def.h"

typedef struct 
{
	u32 SCER;
	u32 SCDR;
	u32 SCSR;
	u32 reserved0;
	u32 PCER0;
	u32 PCDR0;
	u32 PCSR0;
	u32 reserved1;
	u32 CKGR_MOR;
	u32 CKGR_MCFR;
	u32 CKGR_PLLAR;
	u32 CKGR_PLLBR;
	u32 MCKR;
	u32 reserved2;
	u32 USB;
	u32 reserved3;
	u32 PCK0;
	u32 PCK1;
	u32 PCK2;
	u32 reserved4;
	u32 reserved5;
	u32 reserved6;
	u32 reserved7;
	u32 reserved8;
	u32 reserved9;
	u32 IER;
	u32 IDR;
	u32 SR;
	u32 IMR;
	u32 FSMR;
	u32 FSPR;
	u32 FOCR;
	u32 reserved10[25];
	u32 WPMR;
	u32 WPSR;
	u32 reserved11[4];
	u32 PCER1;
	u32 PCDR1;
	u32 PCSR1;
	u32 OCR;
} pmc_registers;

#define PMC_BASE ( ( volatile pmc_registers * ) 0x400E0400 )

void enable_main_clock();
void enable_peripheral_clock( int );

#endif