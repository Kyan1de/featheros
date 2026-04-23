#include <idt.h>
#include <kconsole.h>

__attribute__((aligned(0x10)))
static idt_entry_t IDT[256];

typedef struct {
	uint64_t offset;
	uint16_t size;
} __attribute__((packed)) idtr_t;

static idtr_t idtr = {
	.size = sizeof(IDT)/sizeof(idt_entry_t),
	.offset = (uint64_t)&IDT,
};

__attribute__((noreturn))
void exc_general_handler() {
	asm volatile ("cli; hlt"); // crash and burn
}

void idt_init(void) {
	for (int ii = 0; ii < 32; ii++) {
		MAKEIDTENTRY(exc_general_handler, INT_GATE, ii);
	}
	asm volatile ("lidt %0" : : "m"(idtr) : ); 
	asm volatile ("sti"); 
}

/* we'll be making more refined handlers later, for now we just catch fire. 
__attribute__((interrupt)) void zerodiv_handler(struct interrupt_frame frame) {
	kprint("Division error at cs = ");
	kprint_hex64(frame.cs);
	kprint(" and rip = ");
	kprint_hex64(frame.rip);
}
*/

