#include <idt.h>
#include <kconsole.h>


idt_entry IDT[];

typedef struct {
	uint64_t offset;
	uint16_t size;
} __attribute__((packed)) IDTR;

IDTR idt_descriptor = {
	.size = sizeof(IDT)/sizeof(idt_entry),
	.offset = &IDT,
}

void idt_init(void) {
	asm volatile ("lidt %0" : : "m"(idt_descriptor) : ); 
}

__attribute__((interrupt)) void interrupt_handler(struct interrupt_frame* frame) {
	kprint("Division error at ");
	kprint_hex64(frame-> //man idk if this is right come back later ig
}

idt_entry IDT[] = {
	MAKEIDTENTRY(func, gate_t),
}
