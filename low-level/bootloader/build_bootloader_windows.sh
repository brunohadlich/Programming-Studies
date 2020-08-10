#Build floppy.img based on Microsoft Windows Portable Executable
gcc -fno-pie -std=c99 -c -g -Os -march=i686 -m32 -ffreestanding -Wall -Werror test.c
ld -mi386pe -static -T test.ld -nostdlib --nmagic -o test.pe test.o
objcopy --set-section-flags .sig=alloc,contents,load,data,readonly test.pe test.pe
objcopy -O binary test.pe test.bin
dd if=/dev/zero of=floppy.img bs=512 count=2880
dd if=test.bin of=floppy.img
