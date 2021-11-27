del /F /Q builds\*

mkdir builds\src
mkdir builds\src\cpu
mkdir builds\src\drivers
mkdir builds\src\sajclib

nasm bootloader\boot.asm -o builds\boot.o

make -C kernel --debug

copy builds\boot.o/b+builds\kernel/b builds\os.bin

qemu-system-x86_64 -fda builds\os.bin