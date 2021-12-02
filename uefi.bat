del /F /Q builds

mkdir builds
mkdir builds\uefi

make -C uefi

powershell -Command "& {Mount-DiskImage D:\mj\code\tutorial\os\disk\vd1.vhd;}"


del /F /Q e:\EFI\Boot\*

mkdir e:\EFI
mkdir e:\EFI\Boot

copy builds\uefi\*.efi e:\EFI\Boot

ren e:\EFI\Boot\mj.efi bootx64.efi

powershell -Command "& {Dismount-DiskImage D:\mj\code\tutorial\os\disk\vd1.vhd;}"

qemu-system-x86_64 -bios utilities\OVMF.fd -hdd D:\mj\code\tutorial\os\disk\vd1.vhd