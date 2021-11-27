CC = clang
GDB = gdb 

LD = ld.lld
ASM = nasm

BUILDS = ../builds

CCFLAGS = -Iinc -ggdb -c -ffreestanding -target x86_64-none-elf
LDFLAGS = -Ttext 0x9000
LDFLAGS_BIN = ${LDFLAGS} --oformat binary
ASFLAGS = -f elf64

SRC = $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c) $(wildcard */*/*/*.c)
ASM_SRC = $(wildcard *.asm) $(wildcard */*.asm) $(wildcard */*/*.asm) $(wildcard */*/*/*.asm)

OBJ = ${ASM_SRC:%.asm=${BUILDS}/%.o} ${SRC:%.c=${BUILDS}/%.o} 

all: kernel kernel.elf

kernel: ${OBJ}
	${LD} -o ${BUILDS}/$@ ${LDFLAGS_BIN} $^

kernel.elf: ${OBJ}
	${LD} -o ${BUILDS}/$@ ${LDFLAGS} $^

${BUILDS}/%.o: %.c
	${CC} ${CCFLAGS}  -o ${BUILDS}/$@ $^

${BUILDS}/%.o: %.asm
	${ASM} $< ${ASFLAGS} -o ${BUILDS}/$@

clean:
	del /F /Q builds\*