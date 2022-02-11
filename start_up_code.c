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
// User specific interrupts
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
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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
