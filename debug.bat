
start qemu-system-x86_64 -fda builds\os.bin -s -S &
gdb -ex "target remote localhost:1234" -ex "symbol-file builds/kernel.elf" -ex "break *0x9000"