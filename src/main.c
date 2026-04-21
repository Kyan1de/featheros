#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

// shit i made
#include <util.h>
#include <kalloc.h>
#include <kconsole.h>
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

	// Fetch the first framebuffer.
	struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
	kconsole_init(framebuffer);
	kprint_u64(69420);
	kprint("\n");
	kprint_u8(255);
	kprint("\n");
	kprint_hex64(69420);
	kprint("\n");
	kprint_i64(-1);
	kprint("\n");
	kprint_i64(0);
	kprint("\n");
	kprint_u64(0);
	kprint("\n");
	// We're done, just hang...
	for (;;) {}
}

