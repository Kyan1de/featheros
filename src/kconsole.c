#include <kconsole.h>
#include <stdint.h>
#include <chardata.h>
#include <util.h>
#include <limine.h>

size_t scr_start = 0;
size_t buf_offset = 0;
char buffer[CON_BUFSIZE];

struct {
	uint32_t* ptr;
	uint64_t width, height;
} screendat;

#define characterdat(ord) ((((ord)-32 < 0 || (ord)-32 > 16*8) ? (ord)-32 : 0 ) * CON_CHAR_HEIGHT)


void kconsole_init(lfb *fb) {
	memset(buffer, 0, sizeof(buffer));
	memset(fb->address, 0, fb->height*fb->width*4); // *4 because 32 bit fb is assumed
	screendat.ptr = fb->address;
	screendat.width = fb->width;
	screendat.height = fb->height;
	kprint("Console initialized");
}

void draw_char(uint64_t left, uint64_t top, char ch) {
	size_t charidx = characterdat(ch);
	for (int y = 0; y < CON_CHAR_HEIGHT; y++) {
		for (int x = 0; x < CON_CHAR_WIDTH; x++) {
			int draw = chardat[y + charidx] & ((1 << 8) >> x);
			if (draw) *(screendat.ptr + (size_t)top*screendat.width + (size_t)left) = COL_WHITE;
		}
	}
}

void draw_console() {
	scr_start = RANGEROUNDDOWN((uint64_t)buf_offset - CON_SIZE, CON_WIDTH); // align to a line
	memset(screendat.ptr, 0, screendat.height*screendat.width*4); // *4 because 32 bit fb is assumed
	for (int ii = 0; ii < CON_SIZE; ii++) {
		draw_char((ii%CON_WIDTH)*screendat.width, (ii/CON_WIDTH)*screendat.height, buffer[(scr_start + ii) % CON_BUFSIZE]);
	}
}

void kprint(const char* s) {
	// read the string until we read a zero, copying to the buffer as we go
	while (*s) {
		buffer[buf_offset] = *s;
		s++;
		buf_offset++;
		buf_offset %= CON_BUFSIZE;
	}
	draw_console();

}
