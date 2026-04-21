#include <stdint.h>
#include <util.h>

// assuming 24 bit RGB in the last 24 bits of a 32 bit value. may refactor later.
#define COL_RED 	0x00FF0000
#define COL_GREEN 	0x0000FF00
#define COL_BLUE 	0x000000FF
#define COL_GRAY 	0x00AAAAAA
#define COL_WHITE 	0xa0FFFFFF
#define COL_BLACK 	0x00000000
// for now we can use the upper byte of the colour to include some data 
// to optimize the draw call for the console by storing the character drawn

// screen defines
#define CON_WIDTH 120
#define CON_HEIGHT 48
#define CON_SIZE (CON_WIDTH*CON_HEIGHT)
#define CON_CHAR_WIDTH 6
#define CON_CHAR_HEIGHT 12
#define CON_BUFSIZE (CON_SIZE*2)

void kconsole_init(lfb *fb);
void kputc(char c);
void kprint(const char* s);

// for integers
void kprint_u64(uint64_t i);
void kprint_u32(uint32_t i);
void kprint_u16(uint16_t i);
void kprint_u8(uint8_t i);
void kprint_i64(int64_t i);
void kprint_i32(int32_t i);
void kprint_i16(int16_t i);
void kprint_i8(int8_t i);

// for hex data
void kprint_hex8(uint8_t i);
void kprint_hex16(uint16_t i);
void kprint_hex32(uint32_t i);
void kprint_hex64(uint64_t i);
