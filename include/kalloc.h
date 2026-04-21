#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include <util.h>

#ifndef k_kalloc_h
#define k_kalloc_h

// converts between physical and virtual addresses. while we do currently know the exact kernel start address and could use it as a constant, idk if it will change later on and would rather leave it to be dynamic until necessary to refactor
#define to_phys_addr(i) ((i) - *(size_t*)kernel_start)
#define to_virt_addr(i) ((i) + *(size_t*)kernel_start)

typedef void* freemarker;



void kmalloc_init(volatile struct limine_memmap_request* mmap); // sets up memory allocation, and informs the kernel of the 
void* kmalloc(size_t n); // returns ptr to memory allocated, or NULL on failure

#endif // k_kalloc_h
