extern _idt
extern _isr1_Handler
global _isr1
global _loadIdt

idtDesc:
	dw 2048
	dd _idt

_isr1:
	pushad
	call _isr1_Handler
	popad
	iretd

_loadIdt:
	lidt[idtDesc]
	sti
	ret