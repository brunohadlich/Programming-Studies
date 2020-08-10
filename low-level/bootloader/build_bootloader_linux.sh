#Build floppy.img based on Linux ELF
#gcc -c -g -Os -m32 -ffreestanding -Wall -Werror test.c -o test.o
gcc -c -g -Os -m32 -ffreestanding -Wall -Werror test.c -o test.o
ld -m elf_i386 -static -Ttest.ld -nostdlib --nmagic -o test.elf test.o
objcopy -O binary test.elf test.bin
dd if=/dev/zero of=floppy.img bs=512 count=2880
dd if=test.bin of=floppy.img
