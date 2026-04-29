#include <stdint.h>
#include <stdbool.h>

#ifndef IDT_H
#define IDT_H

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t limit;
	uint64_t base;
} __attribute__((packed)) idtr_t;


void idt_init(void);
__attribute__((noreturn)) void exception_handler(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

extern void* isr_stub_table[];
static bool vectors[IDT_MAX_DESCRIPTORS];

#define PIC1		0x20		/* IO base address for main PIC */
#define PIC2		0xA0		/* IO base address for secondary PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define PIC_EOI		0x20		/* End-of-interrupt command code */
#define PIC_INIT	0x11		/* End-of-interrupt command code */

#endif // IDT_H
