[bits 32]
[extern main]
section .text
global kmain
kmain:
call main
jmp $
