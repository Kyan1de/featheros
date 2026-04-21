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


#define characterdat(ord) ((((ord)-32 < 0 || (ord)-32 > 16*8) ? 16*8 : (ord)-32 ) * CON_CHAR_HEIGHT)


void kconsole_init(lfb *fb) {
	memset(buffer, 0, sizeof(buffer));
	screendat.ptr = fb->address;
	screendat.width = fb->width;
	screendat.height = fb->height;
	kprint("Console initialized\n");
}

void draw_char(uint64_t left, uint64_t top, char ch) {
	size_t charidx = characterdat(ch);
	uint64_t col_fg = ch << 24 | COL_WHITE;
	uint64_t col_bg = ch << 24 | COL_BLACK;
	for (int y = 0; y < CON_CHAR_HEIGHT; y++) {
		for (int x = 0; x < CON_CHAR_WIDTH; x++) {
			int draw = chardat[charidx + y] & (0x80 >> x);
			if (draw != 0)
				screendat.ptr[(size_t)(y+top)*screendat.width + (size_t)(x+left)] = col_fg;
			else
				screendat.ptr[(size_t)(y+top)*screendat.width + (size_t)(x+left)] = col_bg;
		}
	}
}

void draw_console() {
	scr_start = 0;//RANGEROUNDDOWN((uint64_t)buf_offset - CON_SIZE, CON_WIDTH); // align to a line
	uint64_t draw_offset = 0;
	for (int ii = 0; ii < CON_SIZE; ii++) {
		char ch = buffer[(scr_start + ii) % CON_BUFSIZE];
		if (ch == '\n') {draw_offset = RANGEROUNDDOWN(draw_offset+CON_WIDTH, CON_WIDTH); continue;} // minus 1 since ii increments on continue
		if (ch == 0) continue;
		uint64_t left = (draw_offset%CON_WIDTH)*CON_CHAR_WIDTH;
		uint64_t top = (draw_offset/CON_WIDTH)*CON_CHAR_HEIGHT;
		if (screendat.ptr[(size_t)top*screendat.width + left] >> 24 == ch) {draw_offset++; continue;}
		draw_char(left, top, ' ');
		draw_char(left, top, ch);
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

void kputc(char c) {
	buffer[buf_offset] = c;
	buf_offset++;
	buf_offset %= CON_BUFSIZE;
	draw_console();
}


char intbuf[21] = {0}; // buffer for the integer printing functions

#define uintprintfunc(append) \
void kprint_u##append (uint##append##_t i) { \
	size_t offset = 20; \
	intbuf[offset] = '0'; \
	if (i == 0) { \
		offset--; \
	} \
	while (i) { \
		intbuf[offset] = '0' + (uint8_t)(i % 10); \
		i /= 10; \
		offset--; \
	} \
	kprint(intbuf + offset + 1); \
	memset(intbuf, 0, sizeof(intbuf)); \
}

#define intprintfunc(append) \
void kprint_i##append (int##append##_t i) { \
	size_t offset = 20; \
	int negative = (i < 0); \
	if (negative) i = -i; \
	intbuf[offset] = '0'; \
	if (i == 0) { \
		offset--; \
	} \
	while (i) { \
		intbuf[offset] = '0' + (uint8_t)(i % 10); \
		i /= 10; \
		offset--; \
	} \
	if (negative) {intbuf[offset] = '-'; offset--;} \
	kprint(intbuf + offset + 1); \
	memset(intbuf, 0, sizeof(intbuf)); \
}

#define hexprintfunc(append) \
void kprint_hex##append (uint##append##_t i) { \
	const char hex[] = "0123456789ABCDEF"; \
	size_t offset = 20; \
	intbuf[offset] = '0'; \
	if (i == 0) { \
		offset--; \
	} \
	while (i) { \
		intbuf[offset] = hex[i & 0x0F]; \
		i = i >> 4; \
		offset--; \
	} \
	kprint(intbuf + offset + 1); \
	memset(intbuf, 0, sizeof(intbuf)); \
}

uintprintfunc(64);
uintprintfunc(32);
uintprintfunc(16);
uintprintfunc(8);
intprintfunc(64);
intprintfunc(32);
intprintfunc(16);
intprintfunc(8);
hexprintfunc(64);
hexprintfunc(32);
hexprintfunc(16);
hexprintfunc(8);

