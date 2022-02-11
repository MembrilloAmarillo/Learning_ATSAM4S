CC      = arm-none-eabi-gcc
OBJDUMP = arm-none-eabi-objdump
OBJCOPY = arm-none-eabi-objcopy
ARM_ASM = arm-none-eabi-as

CFLAGS :=
CFLAGS += -x c -mthumb -ffunction-sections -O1 -mlong-calls 
CFLAGS += -g3 -Wall -mcpu=cortex-m4 -c -fdata-sections -ffreestanding

LDFLAGS :=
LDFLAGS += -mthumb -Wl,-Map=output/main.map -Wl,--start-group -Wl,--end-group
LDFLAGS += -Wl,--gc-sections -mcpu=cortex-m4 -Tlinker.ld

OBJ = main.o start_up_code.o uart.o PMC.o GPIO.o

OBJECTS = $(addprefix output/, $(OBJ))
INC = uart.h PMC.h GPIO.h def.h

.SECONDARY: $(OBJECTS)

.PHONY : clean
all: elf lss bin run

elf: output/main.elf
lss: output/main.lss
bin: output/main.bin

%.lss : %.elf
	@mkdir -p $(dir $@)
	@$(OBJDUMP) -h -S $< > $@
	@echo $@ 

%.bin : %.elf
	@mkdir -p $(dir $@)
	@$(OBJCOPY) -O binary $< $@
	@echo $@

%.elf : $(OBJECTS)
	@mkdir -p $(dir $@)
	@$(CC) $(LDFLAGS) -Wl,--print-memory-usage $^ -o $@
	@echo $@

output/%.o : %.c $(INC)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo $<

run:
	@C:\dev\repos\edbg\edbg.exe -b -t sam4s -s 0 -f output/main.bin -c 9600 -pv

clean:
	rm -rf output/


