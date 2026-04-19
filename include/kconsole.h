#include <stdint.h>
#include <util.h>

// assuming 24 bit RGB in the last 24 bits of a 32 bit value. may refactor later
#define COL_RED 	0x00FF0000
#define COL_GREEN 	0x0000FF00
#define COL_BLUE 	0x000000FF
#define COL_GRAY 	0x00AAAAAA
#define COL_WHITE 	0x00FFFFFF
#define COL_BLACK 	0x00000000

// screen defines
#define CON_WIDTH 80
#define CON_HEIGHT 48
#define CON_SIZE CON_WIDTH*CON_HEIGHT
#define CON_CHAR_WIDTH 6
#define CON_CHAR_HEIGHT 12
#define CON_BUFSIZE CON_SIZE*2

void kconsole_init(lfb *fb);
void kputc(char c);
void kprint(const char* s);
