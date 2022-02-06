#ifndef _FLASH_H_
#define _FLASH_H_

#include "def.h"

typedef struct
{
	u32 FMR;
	u32 FCR;
	u32 FSR;
	u32 FRR;
	u32 reserved[4];
} flash_register;

#define EEFC ( ( volatile flash_register* ) 0x400E0A00 )

#endif 