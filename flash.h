#ifndef _FLASH_H_
#define _FLASH_H_

#include "def.h"

typedef struct
{
	volatile u32 FMR;
	volatile u32 FCR;
	volatile u32 FSR;
	volatile u32 FRR;
	volatile u32 reserved[4];
} Flash_Register;

#define EEFC ( ( Flash_Register* ) 0x400E0A00 )

#endif 