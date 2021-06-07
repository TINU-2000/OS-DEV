[org 0x7c00]

[bits 16]

;Switch To Protected Mode
cli ; Turns Interrupts off
lgdt [GDT_DESC] ; Loads Our GDT

mov eax , cr0
or  eax , 0x1
mov cr0 , eax ; Switch To Protected Mode

jmp  CODE_SEG:INIT_PM ; Jumps To Our 32 bit Code
;Forces the cpu to flush out contents in cache memory

[bits 32]

INIT_PM:
mov ax , DATA_SEG
mov ds , ax
mov ss , ax
mov es , ax
mov fs , ax
mov gs , ax

mov ebp , 0x90000
mov esp , ebp ; Updates Stack Segment





jmp $ ;Hang , Remove This To Start Doing Things In 32 bit Mode





GDT_BEGIN:

GDT_NULL_DESC:  ;The  Mandatory  Null  Descriptor
	dd 0x0
	dd 0x0

GDT_CODE_SEG:
	dw 0xffff		;Limit
	dw 0x0			;Base
	db 0x0			;Base
	db 10011010b	;Flags
	db 11001111b	;Flags
	db 0x0			;Base

GDT_DATA_SEG:
	dw 0xffff		;Limit
	dw 0x0			;Base
	db 0x0			;Base
	db 10010010b	;Flags
	db 11001111b	;Flags
	db 0x0			;Base

GDT_END:

GDT_DESC:
	dw GDT_END - GDT_BEGIN - 1
	dd GDT_BEGIN

CODE_SEG equ GDT_CODE_SEG - GDT_BEGIN
DATA_SEG equ GDT_DATA_SEG - GDT_BEGIN

times 510-($-$$) db 0
dw 0xaa55
