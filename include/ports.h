
static inline void outb(uint16_t port, uint8_t val);  // send (8 bit) byte to port
static inline void outw(uint16_t port, uint16_t val); // send (16 bit) word to port
static inline void outl(uint16_t port, uint32_t val); // send (32 bit) long to port

static inline uint8_t inb(uint16_t port); // read (8 bit) byte from port
static inline uint16_t inw(uint16_t port); // read (16 bit) word from port
static inline uint32_t inl(uint16_t port); // read (32 bit) long from port


