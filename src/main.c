#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

// shit i made
#include <util.h>
#include <kalloc.h>
#include <limineconf.h>

// Halt and catch fire function.
static void hcf(void) {
	for (;;) {
		asm ("hlt");
	}
}

// The following will be our kernel's entry point.
// If renaming kmain() to something else, make sure to change the
// linker script accordingly.
void kmain(void) {
	if (cpuid() == 0) {
		// Ensure the bootloader actually understands our base revision (see spec).
		if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) {
			hcf();
		}

		// Ensure we got a framebuffer.
		if (framebuffer_request.response == NULL
		 || framebuffer_request.response->framebuffer_count < 1) {
			hcf();
		}

		// Ensure that we have memory... or something like that
		if (memmap_request.response == NULL) hcf();
		kmalloc_init(&memmap_request);

		// Fetch the first framebuffer.
		struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

		// Print a nice pattern to screen as an example.
		// Note: we assume the framebuffer model is RGB with 32-bit pixels.
		volatile uint32_t *fb_ptr = framebuffer->address;
		for (size_t y = 0; y < framebuffer->height; y++) {
			for (size_t x = 0; x < framebuffer->width; x++) {
				uint32_t nX = x * 255 / framebuffer->width;
				uint32_t nY = y * 255 / framebuffer->height;
				fb_ptr[y * (framebuffer->pitch / 4) + x] = (nY << 16) | nX;
			}
		}

		// We're done, just hang...
		hcf();
	} else {
		// nothing to do, just hang...
		hcf();
	}
}

