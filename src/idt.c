#include <idt.h>
#include <kconsole.h>

__attribute__((aligned(0x10))) static idt_entry_t idt[IDT_MAX_DESCRIPTORS];
static idtr_t idtr;

void exception_handler() {
	kprint("test");
	asm volatile ("cli; hlt"); // crash and burn
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
	idt_entry_t* descriptor = &idt[vector];

	descriptor->isr_low	= (uint64_t)isr & 0xFFFF;
	descriptor->kernel_cs	= 0;
	descriptor->ist		= 0;
	descriptor->attributes	= flags;
	descriptor->isr_mid	= ((uint64_t)isr >> 16) & 0xFFFF;
	descriptor->isr_high	= ((uint64_t)isr >> 32) & 0xFFFFFFFF;
	descriptor->reserved	= 0;
}



void idt_init() {
	idtr.base = (uintptr_t)&idt[0];
	idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

	for (uint8_t vector = 0; vector < 32; vector++) {
		idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
		vectors[vector] = true;
	}

	__asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
	__asm__ volatile ("sti"); // set the interrupt flag
}



void PIC_sendEOI(uint8_t irq)
{
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);

	outb(PIC1_COMMAND,PIC_EOI);
}
