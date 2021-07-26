[bits 32]

extern _blockAddr
extern _At
global _read
global _write

_read:

		pushfd
		and eax , 0x0FFFFFFF
		push eax
		push ebx
		push ecx
		push edx
		push edi

		mov eax , [_blockAddr]
		mov cl , 1
		mov edi , _At		

		mov ebx , eax
 
		mov edx , 0x01F6 
		shr eax , 24
		or al , 11100000b     ; Sets bit 6 in al for LBA mode
		out dx , al
 
		mov edx , 0x01F2      ; Port to send number of sectors
		mov al , cl           ; Get number of sectors from CL
		out dx , al
 
		mov edx , 0x1F3       ; Port to send bit 0 - 7 of LBA
		mov eax , ebx         ; Get LBA from EBX
		out dx , al
 
		mov edx , 0x1F4       ; Port to send bit 8 - 15 of LBA
		mov eax , ebx         ; Get LBA from EBX
		shr eax , 8           ; Get bit 8 - 15 in AL
		out dx , al
 
 
		mov edx , 0x1F5       ; Port to send bit 16 - 23 of LBA
		mov eax , ebx         ; Get LBA from EBX
		shr eax , 16          ; Get bit 16 - 23 in AL
		out dx , al
 
		mov edx , 0x1F7       ; Command port
		mov al , 0x20         ; Read with retry.
		out dx , al
 
.loop1:
		in al , dx
		test al , 8
		jz .loop1
 
		mov eax , 256         ; Read 256 words , 1 sector
		xor bx , bx
		mov bl , cl           ; read CL sectors
		mul bx
		mov ecx , eax         
		mov edx , 0x1F0
		rep insw             ; copy to [RDI]
 
		pop edi
		pop edx
		pop ecx
		pop ebx
		pop eax
		popfd
		ret


_write:
		pushfd
		and eax , 0x0FFFFFFF
		push eax
		push ebx
		push ecx
		push edx
		push edi

		mov eax , [_blockAddr]
		mov cl , 1
		mov edi , _At

		mov ebx , eax
 
		mov edx , 0x01F6
		shr eax , 24
		or al , 11100000b     ; Set bit 6 in al for LBA mode
		out dx , al
 
		mov edx , 0x01F2      ; Port to send number of sectors
		mov al , cl           ; Get number of sectors from CL
		out dx , al
 
		mov edx , 0x1F3       ; Port to send bit 0 - 7 of LBA
		mov eax , ebx         ; Get LBA from EBX
		out dx , al
 
		mov edx , 0x1F4       ; Port to send bit 8 - 15 of LBA
		mov eax , ebx         ; Get LBA from EBX
		shr eax , 8           ; Get bit 8 - 15 in AL
		out dx , al
 
 
		mov edx , 0x1F5       ; Port to send bit 16 - 23 of LBA
		mov eax , ebx         ; Get LBA from EBX
		shr eax , 16          ; Get bit 16 - 23 in AL
		out dx , al
 
		mov edx , 0x1F7       ; Command port
		mov al , 0x30         ; Write with retry.
		out dx , al
 
.loop2:
		in al , dx
		test al , 8
		jz .loop2
 
		mov eax , 256         ; Read 256 words , 1 sector
		xor bx , bx
		mov bl , cl           ; write CL sectors
		mul bx
		mov ecx , eax 
		mov edx , 0x1F0
		mov esi , edi
		rep outsw            ; go out
 
		pop edi
		pop edx
		pop ecx
		pop ebx
		pop eax
		popfd
		ret
