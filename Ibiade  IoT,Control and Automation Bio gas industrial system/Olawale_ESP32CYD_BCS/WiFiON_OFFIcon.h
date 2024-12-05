#define R 0xE0,
#define G 0x1C,
#define B 0x03,
#define C 0x1F,
#define M 0xE3,
#define Y 0xFC,
#define W 0xFF,
#define _ 0x00,

constexpr uint8_t On[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x31, 0x51, 0x31, 0x31, 0x2d, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x51, 0x55, 0x35, 0x35, 0x35, 0x35, 0x35, 0x55, 0x51, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x2d, 0x55, 0x35, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x35, 0x55, 0x2d, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x04, 0x51, 0x55, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x55, 0x31, 0x04, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x04, 0x51, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x51, 0x04, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x04, 0x51, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x34, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x51, 0x04, 0x00, 0x00, 
  0x00, 0x00, 0x2d, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x55, 0x55, 0x55, 0x55, 0x55, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x55, 0x2d, 0x00, 0x00, 
  0x00, 0x28, 0x55, 0x14, 0x14, 0x14, 0x14, 0x34, 0x55, 0x51, 0x4d, 0x29, 0x09, 0x29, 0x2d, 0x51, 0x55, 0x35, 0x14, 0x14, 0x14, 0x35, 0x55, 0x04, 0x00, 
  0x04, 0x51, 0x35, 0x14, 0x14, 0x14, 0x35, 0x51, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x51, 0x35, 0x14, 0x14, 0x14, 0x35, 0x51, 0x00, 
  0x2d, 0x35, 0x14, 0x14, 0x14, 0x35, 0x51, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x51, 0x35, 0x14, 0x14, 0x14, 0x35, 0x08, 
  0x51, 0x35, 0x14, 0x14, 0x35, 0x51, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x51, 0x35, 0x14, 0x14, 0x35, 0x51, 
  0x2d, 0x35, 0x14, 0x35, 0x51, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x55, 0x14, 0x14, 0x35, 0x2d, 
  0x04, 0x55, 0x35, 0x55, 0x28, 0x00, 0x00, 0x00, 0x00, 0x04, 0x2d, 0x2d, 0x2d, 0x2d, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x35, 0x35, 0x55, 0x04, 
  0x00, 0x31, 0x55, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x08, 0x51, 0x55, 0x55, 0x55, 0x55, 0x55, 0x51, 0x04, 0x00, 0x00, 0x00, 0x00, 0x51, 0x55, 0x4d, 0x00, 
  0x00, 0x04, 0x51, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x55, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x55, 0x08, 0x00, 0x00, 0x00, 0x04, 0x72, 0x00, 0x00, 
  0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x28, 0x55, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x55, 0x04, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x55, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x55, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x35, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x35, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x29, 0x55, 0x14, 0x14, 0x14, 0x14, 0x35, 0x55, 0x55, 0x55, 0x35, 0x15, 0x14, 0x14, 0x14, 0x55, 0x25, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x29, 0x35, 0x14, 0x14, 0x14, 0x55, 0x51, 0x2d, 0x08, 0x2d, 0x51, 0x55, 0x35, 0x14, 0x14, 0x55, 0x49, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x04, 0x55, 0x14, 0x14, 0x55, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x35, 0x14, 0x14, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x35, 0x55, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x35, 0x35, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x51, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x51, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x29, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x2d, 0x51, 0x55, 0x51, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x35, 0x15, 0x14, 0x35, 0x55, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x14, 0x14, 0x14, 0x14, 0x15, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x34, 0x14, 0x14, 0x14, 0x35, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x35, 0x14, 0x14, 0x14, 0x55, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x51, 0x14, 0x14, 0x14, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x35, 0x14, 0x35, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x51, 0x55, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x51, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

constexpr uint8_t Off[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x80, 0x84, 0x84, 0xa9, 0xa4, 0xa4, 0x60, 0x20, 0x00, 0x00, 0x00, 0x64, 0x45, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x45, 0x69, 0x85, 0x64, 0x64, 0x40, 0x64, 0x64, 0x65, 0x69, 0x45, 0x20, 0x20, 0x85, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x84, 0x85, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x64, 0x84, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x40, 0x89, 0x64, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0xa4, 0x60, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x20, 0x89, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0xc4, 0xa5, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x20, 0x69, 0x45, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x40, 0x40, 0x40, 0x20, 0x00, 0x00, 0x20, 0xa5, 0xe0, 0xc4, 0xa4, 0x20, 0x00, 0x00, 
  0x00, 0x00, 0x65, 0x64, 0x00, 0x00, 0x00, 0x00, 0x20, 0x65, 0x89, 0x89, 0x89, 0x89, 0x89, 0x65, 0x20, 0x84, 0xc4, 0xe0, 0xe0, 0xc4, 0x84, 0x00, 0x00, 
  0x00, 0x44, 0x65, 0x00, 0x00, 0x00, 0x20, 0x65, 0x89, 0x69, 0x44, 0x00, 0x00, 0x20, 0x44, 0x65, 0x40, 0xa4, 0xc0, 0xe0, 0xe0, 0xe0, 0xc4, 0x64, 0x00, 
  0x20, 0x65, 0x20, 0x00, 0x00, 0x20, 0x65, 0x85, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x65, 0xa4, 0xc4, 0xe0, 0xe0, 0xe0, 0xc0, 0xa5, 0x20, 
  0x64, 0x45, 0x00, 0x00, 0x00, 0x64, 0x85, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x89, 0x40, 0x84, 0xc4, 0xe0, 0xe0, 0xe0, 0xc4, 0x60, 
  0x85, 0x20, 0x00, 0x00, 0x65, 0x65, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x40, 0x00, 0x20, 0x84, 0xe4, 0xe0, 0xe0, 0xc0, 0x85, 
  0x60, 0x45, 0x00, 0x40, 0x85, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x85, 0x00, 0x00, 0x00, 0x20, 0xa4, 0xe0, 0xe0, 0xc4, 0x60, 
  0x20, 0x89, 0x40, 0x65, 0x40, 0x00, 0x00, 0x00, 0x00, 0x20, 0x64, 0x65, 0x65, 0x65, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc4, 0xc4, 0xa4, 0x20, 
  0x00, 0x44, 0x89, 0x65, 0x00, 0x00, 0x00, 0x00, 0x65, 0x89, 0x85, 0x65, 0x85, 0x60, 0xa4, 0xa5, 0x65, 0x00, 0x00, 0x00, 0x00, 0x84, 0xa5, 0x60, 0x00, 
  0x00, 0x00, 0x69, 0x20, 0x00, 0x00, 0x20, 0x64, 0x89, 0x45, 0x00, 0x00, 0x20, 0x84, 0xc0, 0xe4, 0xc4, 0x64, 0x00, 0x00, 0x00, 0x20, 0x69, 0x00, 0x00, 
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x45, 0x85, 0x40, 0x00, 0x00, 0x00, 0x40, 0xa5, 0xe0, 0xe0, 0xe0, 0xc4, 0x64, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x65, 0x20, 0x00, 0x00, 0x00, 0x00, 0x64, 0xc4, 0xe0, 0xe0, 0xe0, 0xe0, 0xa4, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x20, 0x65, 0x40, 0x00, 0x00, 0x00, 0x00, 0x40, 0xa4, 0xc4, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x84, 0x20, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x40, 0x85, 0x00, 0x00, 0x00, 0x20, 0x40, 0x84, 0xa4, 0xc4, 0xc4, 0xe0, 0xe0, 0xe0, 0xe0, 0xc4, 0x45, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x44, 0x85, 0x00, 0x00, 0x40, 0x85, 0x40, 0x89, 0x40, 0x40, 0x85, 0xc4, 0xe0, 0xe0, 0xe0, 0xc4, 0x45, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0x20, 0x20, 0x89, 0x60, 0x85, 0x44, 0x00, 0x00, 0x00, 0x60, 0xc4, 0xe0, 0xc0, 0xa4, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x64, 0x65, 0x65, 0x40, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0xc5, 0xc4, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x85, 0x65, 0x20, 0x64, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0x85, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x20, 0x20, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x65, 0x40, 0x20, 0x40, 0x60, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x85, 0x20, 0x84, 0xa4, 0xc4, 0xc4, 0x84, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x40, 0x84, 0xc4, 0xc0, 0xe0, 0xc0, 0xc4, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x65, 0x20, 0xa9, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xa9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0x40, 0x00, 0x85, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x65, 0x00, 0x00, 0x60, 0xc4, 0xe0, 0xe0, 0xe0, 0xc4, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x20, 0x00, 0x00, 0x00, 0x84, 0xc0, 0xe0, 0xe0, 0xa5, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc4, 0xc0, 0xc4, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa5, 0xc4, 0xa5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xa9, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x64, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
