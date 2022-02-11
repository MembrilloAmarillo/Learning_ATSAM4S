#include "GPIO.h"
#include "def.h"

void enable_gpio( Gpio_Register* gpio, u32 pin )
{
	gpio->OER |= 1 << pin;
}

void disable_gpio( Gpio_Register* gpio, u32 pin )
{
	gpio->PDR |= 1 << pin;
}

int enable_peripheral_pin( Gpio_Register* gpio, u32 pin, u8 peripheral )
{
	switch( peripheral )
	{
		case PA:
		{
			gpio->ABCDSR1 |= 0 << pin;
    		gpio->ABCDSR2 |= 0 << pin;
		} break;
		case PB:
		{
			gpio->ABCDSR1 |= 1 << pin;
    		gpio->ABCDSR2 |= 0 << pin;
		} break;
		case PC:
		{
			gpio->ABCDSR1 |= 0 << pin;
    		gpio->ABCDSR2 |= 1 << pin;
		}break;
		default:
		{
			return 0;
		} break;
	}
	// Enable PB3 -> UTXD1
    gpio->PDR = 1 << pin; // Enables peripheral control of the pin
    while( ( gpio->PSR & ( 1 << pin ) ) == 1 );

    return 1;
}