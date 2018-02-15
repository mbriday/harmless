AS=arm-none-eabi-as
CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
CFLAGS=-mthumb -mcpu=cortex-m4
EXE=boot.elf

all: $(EXE)

$(EXE): appliFlashAsm.o appliFlash.o
	@$(LD) appliFlashAsm.o appliFlash.o -o $(EXE) -TscriptFlash.ld

appliFlashAsm.o: appliFlashAsm.S
	@$(AS) $(CFLAGS) -c appliFlashAsm.S -o appliFlashAsm.o

appliFlash.o: appliFlash.c
	@$(CC) $(CFLAGS) -c appliFlash.c -o appliFlash.o

clean:
	@rm -f appliFlash.o appliFlashAsm.o $(EXE)
