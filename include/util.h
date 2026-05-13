#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

#ifndef K_UTIL_H
#define K_UTIL_H

void *memcpy(void *restrict dest, const void *restrict src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

// provided by linker, end index of kernel data
// expected to be 64 bit
extern char kernel_start[8]; 
extern char kernel_end[8];

#define VIRT_BITS 0xffff800000000000

#define VIRT_TO_PHYS(addr) ((uint64_t)(addr)&~VIRT_BITS)
#define PHYS_TO_VIRT(addr) ((uint64_t)(addr)|VIRT_BITS)

//typedefs to make C stop complaining
typedef struct limine_framebuffer lfb;

#define RANGEROUNDUP(a, b)  ((a) - ((a)%(b)) + (b))
#define RANGEROUNDDOWN(a, b) ((a) - ((a)%(b)))

// im sure this is std somewhere but idk
#define stringify(x) #x
#define xstringify(x) stringify(x)

//
// inline assembly stuff, may move files later.
//

inline void outb(uint16_t port, uint8_t val) {
	asm volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

inline void outw(uint16_t port, uint16_t val) {
	asm volatile ("outw %w0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

inline void outd(uint16_t port, uint32_t val) {
	asm volatile ("outd %d0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ( "inb %w1, %b0" 
			: "=a"(ret)
			: "Nd"(port)
			: "memory");
	return ret;
}

inline uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ( "inw %w1, %w0" 
			: "=a"(ret)
			: "Nd"(port)
			: "memory");
	return ret;
}

inline uint32_t ind(uint16_t port) {
	uint32_t ret;
	asm volatile ( "ind %w1, %d0" 
			: "=a"(ret)
			: "Nd"(port)
			: "memory");
	return ret;
}

inline void io_wait() {
	outb(0x80, 0);
}

inline void cpuGetMSR(uint32_t msr, uint32_t* lo, uint32_t* hi) {
   asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}

inline void cpuSetMSR(uint32_t msr, uint32_t lo, uint32_t hi) {
   asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}

#endif // K_UTIL_H
