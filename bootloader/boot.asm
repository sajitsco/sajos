org 0x7c00
bits 16

mov bx, 0x7e00 ; Read from disk and store in 0x7e00
mov ax, 0x0240   ; ah <- int 0x13 function. 0x02 = 'read' al <- number of sectors to read (0x01 .. 0x80) . 0x40
mov cx, 0x0002 ; cl <- sector (0x01 .. 0x11) ch <- cylinder (0x0 .. 0x3FF, upper 2 bits in 'cl') dl <- drive number. Our caller sets it as a parameter and gets it from BIOS (0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2)
mov dh, 0x00 ; dh <- head number (0x0 .. 0xF)
int 0x13

jmp switch_to_longmode

times 510 - ($-$$) db 0
dw 0xAA55

switch_to_longmode:
mov dword[0x1000], 0x2003
mov dword[0x2000], 0x3003
mov dword[0x3000], 0x4003
mov edi, 0x4000
mov ebx, 0x00000003
mov ecx, 512
page_table:
    mov dword[edi], ebx
    add edi, 8
    add ebx, 0x1000
loop page_table

cli
mov edi, 0x1000
mov cr3, edi

mov eax, cr4
or  eax, 1 << 5
mov cr4, eax

mov ecx, 0xc0000080
rdmsr
or  eax, 0x00000100
wrmsr

mov ebx, cr0
or  ebx, 0x80000001
mov cr0, ebx

lgdt [GDT.Pointer]

; enable SSE - Float number
mov eax, cr4
or ax, 3 << 9		;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
mov cr4, eax
; end of enableing float operation

jmp 0x0008:0x9000

GDT:
    dq 0
    dq 0x00209a0000000000
    dq 0x0000920000000000
ALIGN 4
    dw 0
    .Pointer:
        dw $ - GDT -1
        dd GDT

times (512 + 512*9) - ($-$$) db 0
