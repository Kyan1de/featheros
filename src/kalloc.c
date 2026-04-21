#include <kalloc.h>

// if this doesnt end up having anyting else in it, refactor to just be some special instance of a freemarker
struct {
	freemarker* freelist;
} kmem;

void kmalloc_init(volatile struct limine_memmap_request* mmap) {
	return;
}

void* kmalloc(size_t n) {
	return NULL;
}

