CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
OBJDUMP=arg-none-eabi-objdump

OBJECTS=main.o system_stm32f4xx.o startup_stm32f411xe.o usart.o gpio.o ringbuffer.o

CMSIS_ROOT=/opt/cross/stm32f4/Drivers/CMSIS

IFLAGS=-I../inc/
IFLAGS+= -I$(CMSIS_ROOT)/Device/ST/STM32F4xx/Include/
IFLAGS+= -I$(CMSIS_ROOT)/Include

CPPFLAGS+= $(IFLAGS)

CFLAGS= --specs=nosys.specs -mthumb -mcpu=cortex-m4 -mfloat-abi=hard
CFLAGS+= -mfpu=fpv4-sp-d16 -DSTM32F411xE -g

ASFLAGS= -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o: %.s
	$(AS) -c $(ASFLAGS) $< -o $@

image.elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -T ../stm32f411re.ld -o image.elf $(OBJECTS)
	objdump -dl image.elf > image.elf.objdump
	
all: image.elf

clean:
	rm -f $(OBJECTS)
	rm -f image.elf