#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

// GCC and Clang reserve the right to generate calls to the following
// 4 functions even if they are not directly called.
// Implement them as the C specification mandates.
// DO NOT remove or rename these functions, or stuff will eventually break!
// They CAN be moved to a different .c file.

void *memcpy(void *restrict dest, const void *restrict src, size_t n) {
	uint8_t *restrict pdest = (uint8_t *restrict)dest;
	const uint8_t *restrict psrc = (const uint8_t *restrict)src;

	for (size_t i = 0; i < n; i++) {
		pdest[i] = psrc[i];
	}

	return dest;
}

void *memset(void *s, int c, size_t n) {
	uint8_t *p = (uint8_t *)s;

	for (size_t i = 0; i < n; i++) {
		p[i] = (uint8_t)c;
	}

	return s;
}

void *memmove(void *dest, const void *src, size_t n) {
	uint8_t *pdest = (uint8_t *)dest;
	const uint8_t *psrc = (const uint8_t *)src;

	if ((uintptr_t)src > (uintptr_t)dest) {
		for (size_t i = 0; i < n; i++) {
			pdest[i] = psrc[i];
		}
	} else if ((uintptr_t)src < (uintptr_t)dest) {
		for (size_t i = n; i > 0; i--) {
			pdest[i-1] = psrc[i-1];
		}
	}

	return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
	const uint8_t *p1 = (const uint8_t *)s1;
	const uint8_t *p2 = (const uint8_t *)s2;

	for (size_t i = 0; i < n; i++) {
		if (p1[i] != p2[i]) {
			return p1[i] < p2[i] ? -1 : 1;
		}
	}

	return 0;
}

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline void outw(uint16_t port, uint16_t val) {
	asm volatile ("outw %w0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline void outd(uint16_t port, uint32_t val) {
	asm volatile ("outd %d0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ( "inb %w1, %b0" 
			: "=a"(ret)
			: "Nd"(port)
			: "memory");
	return ret;
}

static inline uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ( "inw %w1, %w0" 
			: "=a"(ret)
			: "Nd"(port)
			: "memory");
	return ret;
}

static inline uint32_t inb(uint16_t port) {
	uint32_t ret;
	asm volatile ( "ind %w1, %d0" 
			: "=a"(ret)
			: "Nd"(port)
			: "memory");
	return ret;
}

static inline void io_wait() {
	outb(0x80, 0);
}

