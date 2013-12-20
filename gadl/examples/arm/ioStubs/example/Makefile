
CC=arm-none-eabi-gcc
AS=arm-none-eabi-as

CFLAGS = -g -Os
LDFLAGS = -g -Os

SRCS= main.c ../applicationSource/stub.c 
ASM_SRCS = crt0.S 
OBJS = $(SRCS:.c=.o)
OBJS+= $(ASM_SRCS:.S=.o)
EXE=exe

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -Wl,-n,-Tscript.ld,-Map,$(EXE).map

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.S
	$(AS) $< -o $@


clean:
	rm -rf $(OBJS) $(EXE) $(EXE).map *~

