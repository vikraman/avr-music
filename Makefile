CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-mmcu=atmega32 -s -Os

all: player.hex

player.hex: player.elf
	${OBJCOPY} -O ihex player.elf player.hex

player.elf:
	${CC} ${CFLAGS} player.c lcd.c -o player.elf
