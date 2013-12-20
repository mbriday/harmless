ASM_SRCS = add.s crt0.s

EXE = add

ASFLAGS = -mfloat-abi=soft -mcpu=arm7 -g
LDFLAGS = -Wl,-n,-Tscript.ld 
CFLAGS = -nostdlib -mfloat-abi=soft -mcpu=arm7 -g

#############################
## do not modify
#############################

ASM_OBJS = $(ASM_SRCS:.s=.s.o)

all : $(EXE).elf

%.s.o: %.s
	${ARM_XTOOLS}as $(ASFLAGS) $< -o $@

$(EXE).elf : $(ASM_OBJS)
	${ARM_XTOOLS}gcc $(LDFLAGS) $(ASM_OBJS) -o $@ $(CFLAGS)

clean:
	rm -rf $(EXE).elf $(ASM_OBJS)
	