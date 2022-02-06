#include "PMC.h"
#include "flash.h"
#include "def.h"

void enable_main_clock()
{
    EEFC->FMR = ( EEFC->FMR & ~( 0xF << 8 ) ) | ( 5 << 8 );
    // Enable fast crystal oscillator
    u32 MOSCXTST        = ( 1 << 0 );
    BASE_PMC->CKGR_MOR |= ( 1 << 0 ) | ( 0x37 << 16 );
    // MOSCXTST to 100 * 8 = 32 KHz
    while( !( BASE_PMC->SR & MOSCXTST ) );

    // Switch to the main crystal oscillator
    BASE_PMC->CKGR_MOR |= 1 << 24 | ( 0x37 << 16 );
    //u32 MOSCSELS        = 1 << 16;
    //while( !( BASE_PMC->SR & (MOSCSELS) ));
    u32 MCKRDY  = 1 << 3;

    //Program CSS field and wait
    BASE_PMC->MCKR  |= ( 1 << 0 );
    while( !( BASE_PMC->SR & MCKRDY ));
    
    // Program PRES Field and wait
    BASE_PMC->MCKR = 0;
    while( !( BASE_PMC->SR & MCKRDY ));

    /* PCK0 */
    BASE_PMC->SCER = 1 << 8;
    u32 PCKRDY0    = 1 << 8;
    while( !( BASE_PMC->SR & PCKRDY0 ) );
}

void enable_peripheral_clock( int id )
{
    // Enable PCER0
    BASE_PMC->PCER0 |= 1 << id;
    while( ( BASE_PMC->PCSR0 & ( 1 << id ) ) == 0 );
}
