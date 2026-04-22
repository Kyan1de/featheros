#include <stdint.h>

struct interrupt_frame
{
    uint16_t ip;
    uint16_t cs;
    uint16_t flags;
    uint16_t sp;
    uint16_t ss;
};

typedef struct _idt_entry {
	uint16_t offset_1;        // offset bits 0..15
	uint16_t selector;        // a code segment selector in GDT or LDT
	uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
	uint8_t  type_attributes; // gate type, dpl, and p fields
	uint16_t offset_2;        // offset bits 16..31
	uint32_t offset_3;        // offset bits 32..63
	uint32_t zero;            // reserved
} idt_entry

#define INT_GATE 0xE
#define TRAP_GATE 0xF

// NOTE: this is very temporary, will need to come back and refactor when implementing task switching and userspace
#define MAKEIDTENTRY(interrupt, gate_t) \
	struct _idt_entry { \
		.offset_1 = &(interrupt) & 0xFFFF, \
		.selector = 0, \
		.ist = 0, \
		.type_attributes = 0b10000000 | (gate_t << 6), \
		.offset_2 = (&(interrupt) >> 16) & 0xFFFF, \
		.offset_3 = &(interrupt) >> 32, \
		.zero = 0, \
	}


// __attribute__((interrupt)) void interrupt_handler(struct interrupt_frame* frame); is the general form of one of these interrupts

void idt_init(void);
