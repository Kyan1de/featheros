#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

#ifndef k_util_h
#define k_util_h
void *memcpy(void *restrict dest, const void *restrict src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

// provided by linker, end index of kernel data
extern char kernel_start[]; 
extern char kernel_end[];

//typedefs to make C stop complaining
typedef struct limine_framebuffer lfb;

#define RANGEROUNDUP(a, b)  (((a)+(b)-1) & ~((b)-1))
#define RANGEROUNDDOWN(a, b) (((a)) & ~((b)-1))

#endif // k_util_h
