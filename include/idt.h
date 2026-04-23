#include <stdint.h>

struct interrupt_frame
{
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
};

typedef struct _idt_entry {
	uint16_t offset_1;        // offset bits 0..15
	uint16_t selector;        // a code segment selector in GDT or LDT
	uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
	uint8_t  type_attributes; // gate type, dpl, and p fields
	uint16_t offset_2;        // offset bits 16..31
	uint32_t offset_3;        // offset bits 32..63
	uint32_t zero;            // reserved
} __attribute__((packed)) idt_entry_t;

#define INT_GATE 0xE
#define TRAP_GATE 0xF

// NOTE: this is very temporary, will need to come back and refactor when implementing task switching and userspace and actual handlers. For now, we're just using exc_general_handler
#define MAKEIDTENTRY(interrupt, gate_t, idx) \
	struct _idt_entry e = { \
		.offset_1 = (uint64_t)&(interrupt) & 0xFFFF, \
		.selector = 0, \
		.ist = 0, \
		.type_attributes = (uint8_t)0b10000000 | (gate_t << 6), \
		.offset_2 = ((uint64_t)&(interrupt) >> 16) & 0xFFFF, \
		.offset_3 = (uint64_t)&(interrupt) >> 32, \
		.zero = 0, \
	}; \
	IDT[idx] = e


// __attribute__((interrupt)) void interrupt_handler(struct interrupt_frame frame); is the general form of an interrupt handler
// __attribute__((interrupt)) void exception_handler(uint64_t errcode, struct interrupt_frame frame); is the general form of an exception handler with an error code. If the exception does not provide a code, the first argument is omitted. 

void idt_init(void);
