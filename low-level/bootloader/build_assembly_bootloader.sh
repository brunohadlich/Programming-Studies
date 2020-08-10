#Build floppy.img from test.S
as test.S -o test.o
ld -Ttext 0x7c00 --oformat=binary test.o -o test.bin
dd if=/dev/zero of=floppy.img bs=512 count=2880
dd if=test.bin of=floppy.img
