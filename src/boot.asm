; 
; FeatherOS bootloader
;
; Order of operation:
; 	- load kernel into memory
;		- find kernel on disk
;		- load kernel into established 32-bit address
;	- switch into protected mode
;	- jump to kernel
; 

[bits 16]


mov ax, 0x7c0
mov ds, ax
mov [diskNum], dl
mov si, HELLO_STR
call print_str

mov ah, 2 ; read
mov al, 1 ; n sectors
mov ch, 0 ; cyl # 0
mov cl, 1 ; sector #
mov dh, 0 ; head # 0
mov dl, [diskNum] ; disk #
inc dl
; es is the segment used
mov bx, 0x7e0
mov es, bx
xor bx, bx
int 0x13 ; call interrupt to read from disk
jc readerr
cmp al, 1
jne readerr
;otherwise, print the loaded data
mov bx, 0x7e0
mov ds, bx
xor si, si
call print_str
jmp change_mode

readerr:
mov bx, 0x7c0
mov ds, bx
mov si, ERR_STR
call print_str
jmp $

change_mode:
cli
lgdt[GDT_DESCRIPTOR]
; change last bit of cr0 to 1
mov eax, cr0
or eax, 1
mov cr0, eax ; yay 32 bit!
jmp CODE_SEG:start_protected_mode + 0x7c00
%include "src/basic_output.asm"

HELLO_STR: db "Hello, world!",  0x0a, 0x0d, 0x00
diskNum: db 0
ERR_STR: db "Error reading from disk!", 0xa, 0xd, 0x0

%include "src/gdt.asm"

[bits 32]
start_protected_mode:
; print to screen to test if we did it!
mov al, 'A'
mov ah, 0x0f ; white on black
mov [0xb8000], ax ; move character and color bytes to vmem
jmp $

times 510 - ($-$$) db 0
db 0x55, 0xaa


