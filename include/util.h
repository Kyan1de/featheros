#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void kmalloc_init(struct limine_memmap_response* mmap);
void* kmalloc(size_t n);
