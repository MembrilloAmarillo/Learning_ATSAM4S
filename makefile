CC      = arm-none-eabi-gcc
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy
ARM_ASM = arm-none-eabi-as

CFLAGS :=
CFLAGS += -x c -mthumb -ffunction-sections -O1 -mlong-calls 
CFLAGS += -g3 -Wall -mcpu=cortex-m4 -c -fdata-sections -ffreestanding

LDFLAGS :=
LDFLAGS += -mthumb -Wl,-Map=main.map -Wl,--start-group -Wl,--end-group
LDFLAGS += -Wl,--gc-sections -mcpu=cortex-m4 -Tlinker.ld

eeprom := -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma
eeprom += .eeprom=0 --no-change-warnings -O binary

OBJ = main.o start_up_code.o uart.o PMC.o GPIO.c

all: elf lss bin hex

elf: main.elf
lss: main.lss
bin: main.bin
hex: main.hex

main.srec : main.elf
	$(OBJCOPY) -O srec -R .eeprom -R .fuse -R .lock -R .signature $< $@

main.lss : main.elf
	$(OBJDUMP) -h -S $< > $@

main.eep : main.elf
	$(OBJCOPY) $(eeprom) $< $@ || exit 0

main.hex : main.elf
	$(OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

main.bin : main.elf
	$(OBJCOPY) -O binary $< $@

main.elf : $(OBJ)
	$(CC) $(LDFLAGS) -Wl,--print-memory-usage $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run:
	./build.bat

.PHONY : clean

clean:
	rm -rf *.hex *.elf *.o *.map *.exe *.bin *.lss *.eep


