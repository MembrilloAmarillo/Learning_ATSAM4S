#include "PMC.h"
#include "flash.h"
#include "def.h"

void enable_main_clock()
{
    EEFC->FMR = ( EEFC->FMR & ~( 0xF << 8 ) ) | ( 5 << 8 );
    // Enable fast crystal oscillator
    u32 MOSCXTST        = ( 1 << 0 );
    PMC_BASE->CKGR_MOR |= ( 1 << 0 ) | ( 0x37 << 16 );
    // MOSCXTST to 100 * 8 = 32 KHz
    while( !( PMC_BASE->SR & MOSCXTST ) );

    // Switch to the main crystal oscillator
    PMC_BASE->CKGR_MOR |= 1 << 24 | ( 0x37 << 16 );
    //u32 MOSCSELS        = 1 << 16;
    //while( !( PMC_BASE->SR & (MOSCSELS) ));
    u32 MCKRDY  = 1 << 3;

    //Program CSS field and wait
    PMC_BASE->MCKR  |= ( 1 << 0 );
    while( !( PMC_BASE->SR & MCKRDY ));
    
    // Program PRES Field and wait
    PMC_BASE->MCKR = 0;
    while( !( PMC_BASE->SR & MCKRDY ));

    /* PCK0 */
    PMC_BASE->SCER = 1 << 8;
    u32 PCKRDY0    = 1 << 8;
    while( !( PMC_BASE->SR & PCKRDY0 ) );
}

void enable_peripheral_clock( int id )
{
    // Enable PCER0
    PMC_BASE->PCER0 |= 1 << id;
    while( ( PMC_BASE->PCSR0 & ( 1 << id ) ) == 0 );
}
