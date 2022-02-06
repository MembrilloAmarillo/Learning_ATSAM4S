OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm","elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
    vector_table  (rx) : ORIGIN = 0x00400000, LENGTH = 0x200    /* 512 B    */
    flash         (rx) : ORIGIN = 0x00400200, LENGTH = 0xFE00   /* 62.5 KiB */
    sram         (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000  /* 128 KiB  */
}

STACK_SIZE = 16 * 1024;

SECTIONS {  
    .vector_table : {
        KEEP(*(.vector_table))
    } > vector_table

    .text : {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.glue_7)
        *(.glue_7t)
        . = ALIGN(4);
    } > flash

    .rodata : {
        . = ALIGN(4);
        KEEP(*(.rodata))
        KEEP(*(.rodata*))
    } > flash

    . = ALIGN(4);
    linker_data_flash_start = LOADADDR(.data);

    .data : {
        . = ALIGN(4);
        linker_data_ram_start = .;
        KEEP(*(.data))
        KEEP(*(.data*))
        KEEP(*(.ramfunc))
        KEEP(*(.ramfunc*))
        . = ALIGN(4);
        linker_data_ram_end = .;
    } > sram AT > flash

    .bss (NOLOAD) : {
        . = ALIGN(4);
        linker_zero_start = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        linker_zero_end = .;
    } > sram

    .stack (NOLOAD) : {
        . = ALIGN(8);
        . = . + STACK_SIZE;
        . = ALIGN(8);
        linker_stack_end = .;
    } > sram
}
