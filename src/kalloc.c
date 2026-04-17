#include <kalloc.h>

// configuration for kernel level malloc
#define blocksize 512

#define ram_region_protected 1 << 0 // for kernel use

typedef struct {
	size_t base;
	size_t limit;
	uint16_t flags; // usage, owner, etc.
} region_bounds;

static region_bounds* bounds;

void kmalloc_init(volatile struct limine_memmap_request* mmap) {
	return;
}

void* kmalloc(size_t n) {
	return NULL;
}

