GDT_Start:
null_descriptor:
dd 0
dd 0
code_descriptor:
; base 0, limit 0xfffff
; used (1), priv (00), code (1) => 1001 (ppt)
; code (1), conf.(0), read?(1), acc. (0) => 1010 (type)
; gran.(1), 32bs (1), 64bs (0), AVL? (0) => 1100 (other)
dw 0xffff 	; first 16 of limit
dw 0 		; first 24 of base
db 0
db 0b10011010 	; ppt + type flags 
db 0b11001111 	; other flags + last four bits of limit
db 0 		; last 8 bits of base
; whoever designedd this structure is evil.
data_descriptor:
; base 0, limit 0xfffff
; used (1), priv (00), code (1) => 1001 (ppt)
; data (0), dir (0), writ?(1), acc. (0) => 0010 (type)
; gran.(1), 32bs (1), 64bs (0), AVL? (0) => 1100 (other)
dw 0xffff 	; first 16 of limit
dw 0 		; first 24 of base
db 0
db 0b10010010 	; ppt + type flags 
db 0b11001111 	; other flags + last four bits of limit
db 0 		; last 8 bits of base
GDT_End:
GDT_DESCRIPTOR:
dw GDT_End-GDT_Start - 1 	; size
dd GDT_Start			; start

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start
; equ used to set constants
