ASM_SRCS = crt0.s
C_SRCS = basicmath_small_modifie.c cubic.c isqrt.c rad2deg.c
C_SRCS2 = basicmath_large_modifie.c cubic.c isqrt.c rad2deg.c


EXE = basicmath_small_modifie
EXE2 = basicmath_large_modifie

CFLAGS  = -mfloat-abi=soft -mcpu=arm7 -g
ASFLAGS = -mfloat-abi=soft -mcpu=arm7 -g
LDFLAGS = -Wl,-n,-Tscript.ld 
CFLAGS2 = -lm -lc -lgcc -nostdlib -mfloat-abi=soft -mcpu=arm7 -g

#############################
## do not modify
#############################

C_OBJS = $(C_SRCS:.c=.c.o)
C_OBJS2 = $(C_SRCS2:.c=.c.o)
ASM_OBJS = $(ASM_SRCS:.s=.s.o)

all : $(EXE).bin $(EXE2).bin

%.c.o: %.c
	${ARM_XTOOLS}gcc -c $(CFLAGS) $< -o $@

%.s.o: %.s
	${ARM_XTOOLS}as $(ASFLAGS) $< -o $@

$(EXE).elf : $(C_OBJS) $(ASM_OBJS)
	${ARM_XTOOLS}gcc $(LDFLAGS) $(C_OBJS) $(ASM_OBJS) -o $@ $(CFLAGS2)

$(EXE).bin : $(EXE).elf
	${ARM_XTOOLS}objcopy -O binary $< $@

$(EXE2).elf : $(C_OBJS2) $(ASM_OBJS)
	${ARM_XTOOLS}gcc $(LDFLAGS) $(C_OBJS2) $(ASM_OBJS) -o $@ $(CFLAGS2)

$(EXE2).bin : $(EXE2).elf
	${ARM_XTOOLS}objcopy -O binary $< $@


clean:
	rm -rf $(EXE).bin $(EXE).elf $(C_OBJS) $(ASM_OBJS)

#bis:
#	${ARM_XTOOLS}as -mfloat-abi=soft -mcpu=arm7 -g startup.s -o startup.o
#	${ARM_XTOOLS}gcc -c -mfloat-abi=soft -mcpu=arm7 -g test.c -o test.o
#	${ARM_XTOOLS}ld -Ttest.ld test.o startup.o -o test.elf -Map test.map
#	${ARM_XTOOLS}objcopy -O binary test.elf test.bin
	