CRT = crt0.s
ASM_SRCS = nop.s nop1.s add.s add2nondep.s add2dep.s mul.s mul2nondep.s mul2dep.s

ASFLAGS = -mfloat-abi=soft -mcpu=arm7 -g
LDFLAGS = -Wl,-n,-Tscript.ld 
CFLAGS = -nostdlib -mfloat-abi=soft -mcpu=arm7 -g

#############################
## do not modify
#############################

ASM_OBJS = $(ASM_SRCS:.s=.s.o)
CRT_OBJ = $(CRT:.s=.s.o)
ASM_EXE = $(ASM_SRCS:.s=.elf)

all : $(ASM_EXE)

%.s.o: %.s
	${ARM_XTOOLS}as $(ASFLAGS) $< -o $@

%.elf : %.s.o $(CRT_OBJ)
	${ARM_XTOOLS}gcc $(LDFLAGS) $< $(CRT_OBJ) -o $@ $(CFLAGS)

clean:
	rm -rf $(ASM_EXE) $(ASM_OBJS) $(CRT_OBJ)
	