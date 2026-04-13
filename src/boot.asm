; 
; FeatherOS bootloader
;
; Order of operation:
; 	x load kernel into memory
;		- find kernel on disk
;		x load kernel into established 32-bit address
;	x switch into protected mode
;	x jump to kernel
; 

[org 0x7c00]
[bits 16]

KERNEL_LOCATION equ 0x1000

mov [diskNum], dl
mov si, HELLO_STR
call print_str

; load the kernel from after boot sector
mov ah, 2 ; read
mov al, 5 ; n sectors
mov ch, 0 ; cyl # 0
mov cl, 2 ; sector #
mov dh, 0 ; head # 0
mov dl, [diskNum] ; disk #
; es is the segment used
mov bx, 0x0
mov es, bx
mov bx, KERNEL_LOCATION
int 0x13 ; call interrupt to read from disk
jc readerr ; if any error reading the disk, display and halt
cmp al, 5
jne readerr

; otherwise, set text mode and load as normal

mov ah, 0x0
mov al, 0x3
int 10 ; text mode
jmp change_mode

readerr:
mov si, ERR_STR
call print_str
jmp $

change_mode:
cli
xor bx, bx
mov ds, bx
lgdt [GDT_DESCRIPTOR]
; change last bit of cr0 to 1
mov eax, cr0
or eax, 1
mov cr0, eax ; yay 32 bit!
jmp 0x8:fill_segments ; long jump to clear instruction pipeline and set cs

[bits 32]
fill_segments:
mov ax, 0x10 ; 2 (idx of data segment descriptor) * 8 = 0x10
mov ds, ax
mov ss, ax ; both the stack segment and data segment registers will use the data segment descriptor for now
mov esp, 0x090000 ; set stack pointer (*remember stack grows down)
jmp KERNEL_LOCATION

%include "src/basic_output.asm"

HELLO_STR: db "Hello, world!",  0x0a, 0x0d, 0x00
diskNum: db 0
ERR_STR: db "Error reading from disk!", 0xa, 0xd, 0x0

%include "src/gdt.asm"

times 510 - ($-$$) db 0
db 0x55, 0xaa

; end of boot sector, kernel code will be added here after build
