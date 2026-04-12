.PHONY: clean .force-rebuild
all: bootloader.bin test.img

bootloader.bin: .force-rebuild
	nasm -fbin ./src/boot.asm -o ./build/boot.bin

clean: 
	rm ./runtime/*.img
	rm ./build/*

test.img: .force-rebuild
	qemu-img create -f qcow2 -b test.dat -F raw runtime/test.img 1M

run: bootloader.bin test.img
	qemu-system-x86_64\
	       	-drive file=./build/boot.bin,format=raw,index=0\
	        -drive file=./runtime/test.img,index=1\
		-D qemulog.txt\
		-M accel=tcg,smm=off -d int -no-reboot -no-shutdown
