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


#define characterdat(ord) ((((ord)-32 < 0 || (ord)-32 > 16*8) ? 0 : (ord)-32 ) * CON_CHAR_HEIGHT)


void kconsole_init(lfb *fb) {
	memset(buffer, 0, sizeof(buffer));
	screendat.ptr = fb->address;
	screendat.width = fb->width;
	screendat.height = fb->height;
	kprint("Console initialized\n");
}

void draw_char(uint64_t left, uint64_t top, char ch) {
	size_t charidx = characterdat(ch);
	for (int y = 0; y < CON_CHAR_HEIGHT; y++) {
		for (int x = 0; x < CON_CHAR_WIDTH; x++) {
			int draw = chardat[charidx + y] & (0x80 >> x);
			if (draw != 0)
				screendat.ptr[(size_t)(y+top)*screendat.width + (size_t)(x+left)] = COL_WHITE;
			else
				screendat.ptr[(size_t)(y+top)*screendat.width + (size_t)(x+left)] = COL_BLACK;
		}
	}
}

void draw_console() {
	scr_start = 0;//RANGEROUNDDOWN((uint64_t)buf_offset - CON_SIZE, CON_WIDTH); // align to a line
	memset(screendat.ptr, 0, screendat.height*screendat.width*4); // *4 because 32 bit fb is assumed
	uint64_t draw_offset = 0;
	for (int ii = 0; ii < CON_SIZE; ii++) {
		char ch = buffer[(scr_start + ii) % CON_BUFSIZE];
		if (ch == '\n') {draw_offset = RANGEROUNDDOWN(draw_offset+CON_WIDTH, CON_WIDTH); continue;} // minus 1 since ii increments on continue
		draw_char((draw_offset%CON_WIDTH)*CON_CHAR_WIDTH, (draw_offset/CON_WIDTH)*CON_CHAR_HEIGHT, ch);
		draw_offset++;
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
