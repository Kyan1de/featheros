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
extern char kernel_start[]; 
extern char kernel_end[];

//typedefs to make C stop complaining
typedef struct limine_framebuffer lfb;

#define RANGEROUNDUP(a, b)  ((a) - ((a)%(b)) + (b))
#define RANGEROUNDDOWN(a, b) ((a) - ((a)%(b)))


static inline void outb(uint16_t port, uint8_t val);
static inline void outw(uint16_t port, uint16_t val);
static inline void outd(uint16_t port, uint32_t val);

static inline uint8_t inb(uint16_t port);
static inline uint16_t inw(uint16_t port);
static inline uint32_t ind(uint16_t port);

static inline void io_wait();

#endif // K_UTIL_H
