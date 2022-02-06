#include "def.h"
#include "uart.h"

#define TEMPLATE __attribute__((weak, alias("exception_not_implemented")))

static void exception_not_implemented() {
    while (1);
}

extern u32 linker_stack_end;
extern u32 linker_zero_start;
extern u32 linker_zero_end;
extern u32 linker_data_flash_start;
extern u32 linker_data_ram_start;
extern u32 linker_data_ram_end;

extern void main();
static void reset_handler();

TEMPLATE void non_maskable_exception();
TEMPLATE void hard_fault_exception();
TEMPLATE void memory_exception();
TEMPLATE void bus_exception();
TEMPLATE void usage_exception();
TEMPLATE void svc_exception();
TEMPLATE void debug_exception();
TEMPLATE void pendsv_exception();
TEMPLATE void systick_interrupt();
TEMPLATE void sups_interrupt();
TEMPLATE void rstc_interrupt();
TEMPLATE void rtc_interrupt();
TEMPLATE void rtt_interrupt();
TEMPLATE void wdt_interrupt();
TEMPLATE void pmc_interrupt();
TEMPLATE void efc_interrupt();
TEMPLATE void uart0_interrupt();
TEMPLATE void smc_interrupt();
TEMPLATE void gpioa_interrupt();
TEMPLATE void gpiob_interrupt();
TEMPLATE void gpioc_interrupt();
TEMPLATE void gpiod_interrupt();
TEMPLATE void gpioe_interrupt();
TEMPLATE void usart0_interrupt();
TEMPLATE void usart1_interrupt();
TEMPLATE void sd_interrupt();
TEMPLATE void twi0_interrupt();
TEMPLATE void twi1_interrupt();
TEMPLATE void spi_interrupt();
TEMPLATE void dma_interrupt();
TEMPLATE void timer0_interrupt();
TEMPLATE void timer1_interrupt();
TEMPLATE void timer2_interrupt();
TEMPLATE void timer3_interrupt();
TEMPLATE void timer4_interrupt();
TEMPLATE void timer5_interrupt();
TEMPLATE void timer6_interrupt();
TEMPLATE void timer7_interrupt();
TEMPLATE void timer8_interrupt();
TEMPLATE void afe0_interrupt();
TEMPLATE void afe1_interrupt();
TEMPLATE void dac_interrupt();
TEMPLATE void acc_interrupt();
TEMPLATE void arm_interrupt();
TEMPLATE void usb_interrupt();
TEMPLATE void pwm_interrupt();
TEMPLATE void can0_interrupt();
TEMPLATE void can1_interrupt();
TEMPLATE void aes_interrupt();
TEMPLATE void nic_interrupt();
TEMPLATE void uart1_interrupt();

//--------------------------------------------------------------------------------------------------
#define SECTION(x) __attribute__((section(x)))
SECTION(".vector_table") volatile const void* vector_table[] = {
    &linker_stack_end,
    reset_handler,
    non_maskable_exception,
    hard_fault_exception,
    memory_exception,
    bus_exception,
    usage_exception,
    0,
    0,
    0,
    0, 
    svc_exception, 
    debug_exception,
    0,
    pendsv_exception,
    systick_interrupt,
    sups_interrupt,
    rstc_interrupt,
    rtc_interrupt,
    rtt_interrupt,
    wdt_interrupt,
    pmc_interrupt,
    efc_interrupt,
    uart0_interrupt,
    smc_interrupt,
    gpioa_interrupt,
    gpiob_interrupt,
    gpioc_interrupt,
    gpiod_interrupt,
    gpioe_interrupt,
    usart0_interrupt,
    usart1_interrupt,
    sd_interrupt,
    twi0_interrupt,
    twi1_interrupt,
    spi_interrupt,
    dma_interrupt,
    timer0_interrupt,
    timer1_interrupt,
    timer2_interrupt,
    timer3_interrupt,
    timer4_interrupt,
    timer5_interrupt,
    timer6_interrupt,
    timer7_interrupt,
    timer8_interrupt,
    afe0_interrupt,
    afe1_interrupt,
    dac_interrupt,
    acc_interrupt,
    arm_interrupt,
    usb_interrupt,
    pwm_interrupt,
    can0_interrupt,
    can1_interrupt,
    aes_interrupt,
    0,
    0,
    0,
    0,
    nic_interrupt,
    uart1_interrupt
};

//--------------------------------------------------------------------------------------------------

static void reset_handler()
{
    // Relocate data from flash to RAM.
    u32* source = &linker_data_flash_start;
    u32* dest   = &linker_data_ram_start;

    /* Copy .data from flash to sram */
    while (dest < &linker_data_ram_end) {
        *dest++ = *source++;
    }

    // Zero unitinialized data.
    dest = &linker_zero_start;
    // Next initialize to 0 .bss section
    while (dest < &linker_zero_end) {
        *dest++ = 0;
    }

    main();
    while (1);
}
