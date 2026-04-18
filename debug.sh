qemu-system-x86_64 -drive file=image.hdd --no-reboot --no-shutdown -s -S &

gdb	-ex "target remote localhost:1234"\
	-ex "symbol-file obj/kernel.sym"\
	-ex "break kmain"\
	-ex "c"\
	-ex "layout split"\
	-tui
