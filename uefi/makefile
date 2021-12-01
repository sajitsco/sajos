
cc = clang
cflags = -I efi -target x86_64-pc-win32-coff -fno-stack-protector -fshort-wchar -mno-red-zone
ld = lld-link
lflags = -subsystem:efi_application -nodefaultlib -dll

all : main.efi memmap.efi

main.efi : ../builds/uefi/main.obj
	$(ld) $(lflags) -entry:efi_main $< -out:../builds/uefi/$@

memmap.efi : ../builds/uefi/memmap.obj
	$(ld) $(lflags) -entry:efi_main $< -out:../builds/uefi/$@

../builds/uefi/memmap.obj : memmap.c
	$(cc) $(cflags) -c $< -o $@
	
../builds/uefi/main.obj : main.c
	$(cc) $(cflags) -c $< -o $@