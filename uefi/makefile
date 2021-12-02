
cc = clang
cflags = -I efi -target x86_64-pc-win32-coff -fno-stack-protector -fshort-wchar -mno-red-zone
ld = lld-link
lflags = -subsystem:efi_application -nodefaultlib -dll

BUILDS = ../builds/uefi

SRC = $(wildcard *.c)
OBJ = ${SRC:%.c=${BUILDS}/%.obj} 
EFI = ${SRC:%.c=${BUILDS}/%.efi} 


all : ${EFI}

${BUILDS}/%.obj: %.c
	$(cc) $(cflags) -c $< -o $@

${BUILDS}/%.efi: ${BUILDS}/%.obj
	$(ld) $(lflags) -entry:efi_main $< -out:$@

print-%  : ; @echo $* = $($*)
