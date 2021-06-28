nasm Boot.asm -f bin -o bin\bootsect.bin
nasm Kernel_Entry.asm -f elf -o bin\Entry.bin
nasm IDT.asm -f elf -o bin\IDT.bin
nasm ata.asm -f elf -o bin\ata.bin

gcc -m32 -ffreestanding -c main.c -o bin\kernel.o

ld -T NUL -o bin\Kernel.img -Ttext 0x1000 bin\Entry.bin bin\kernel.o bin\IDT.bin bin\ata.bin

objcopy -O binary -j .text  bin\kernel.img bin\kernel.bin
copy /b /Y bin\bootsect.bin+bin\kernel.bin bin\os-image

qemu-system-i386 -drive format=raw,file=bin\os-image
