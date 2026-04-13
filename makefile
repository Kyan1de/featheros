.PHONY: clean .force-rebuild
all: main.img test.img

main.img: bootloader.bin kernel
	cat ./build/boot.bin ./build/kernel.bin > ./build/disk.bin
	qemu-img create -f qcow2 -b disk.bin -F raw build/disk.img 1M

bootloader.bin: .force-rebuild
	nasm -fbin ./src/boot.asm -o ./build/boot.bin

kernel: kernel_entry.o kernel.o
	i386-linux-ld -T link.lds -o ./build/kernel.bin\
		./build/kernel_entry.o\
		./build/kernel.o --oformat binary
kernel_entry.o:
	nasm ./src/kernel_entry.asm -f elf32 -o ./build/kernel_entry.o
kernel.o:
	i386-linux-gcc -ffreestanding -fno-pie -m32 -g -c ./src/kernel.c -o ./build/kernel.o

clean: 
	rm ./runtime/*.img
	rm ./build/*

test.img: .force-rebuild
	qemu-img create -f qcow2 -b test.dat -F raw runtime/test.img 1M

run: all
	qemu-system-x86_64\
	       	-drive file=./build/disk.img,index=0\
	        -drive file=./runtime/test.img,index=1\
		-D qemulog.txt\
		-d int -no-reboot -no-shutdown 
dbg: all
	qemu-system-x86_64\
	       	-drive file=./build/disk.img,index=0\
	        -drive file=./runtime/test.img,index=1\
		-D qemulog.txt\
		-d int -no-reboot -no-shutdown -s -S -d int


