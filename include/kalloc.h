#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

void kmalloc_init(volatile struct limine_memmap_request* mmap); // sets up memory allocation, and informs the kernel of the 
void* kmalloc(size_t n); // returns ptr to memory allocated, or NULL on failure

#define KERNEL_BASE_ADDR 0xffffffff80000000ull
