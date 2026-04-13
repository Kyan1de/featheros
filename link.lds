OUTPUT_FORMAT(elf_i386)

SECTIONS {
	.text : {
		*(.text)
	}

	.bss : {
		*(.bss)
	}

	.data : {
		*(.data)
	}

	.rodata : {
		*(.rodata)
	}
}
