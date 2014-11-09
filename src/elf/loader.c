unsigned char loader[] = {
  0xbd, 0x00, 0x00, 0x00, 0x00, 0xbc, 0x00, 0x00, 0x00, 0x08, 0xe9, 0x21,
  0x01, 0x00, 0x00, 0x90, 0x83, 0xec, 0x08, 0x89, 0x34, 0x24, 0x89, 0x7c,
  0x24, 0x04, 0xfc, 0x8b, 0x4c, 0x24, 0x14, 0x8b, 0x7c, 0x24, 0x0c, 0x8b,
  0x74, 0x24, 0x10, 0xf3, 0xa5, 0x8b, 0x34, 0x24, 0x8b, 0x7c, 0x24, 0x04,
  0x83, 0xc4, 0x08, 0xc3, 0x8d, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x8d, 0xbf,
  0x00, 0x00, 0x00, 0x00, 0x57, 0xfc, 0x8b, 0x4c, 0x24, 0x10, 0x8b, 0x44,
  0x24, 0x0c, 0x8b, 0x7c, 0x24, 0x08, 0xf3, 0xab, 0x5f, 0xc3, 0x8d, 0xb4,
  0x26, 0x00, 0x00, 0x00, 0x00, 0x8d, 0xbc, 0x27, 0x00, 0x00, 0x00, 0x00,
  0x55, 0x57, 0x56, 0x53, 0x83, 0xec, 0x0c, 0x0f, 0xb7, 0x05, 0x2c, 0x00,
  0x00, 0x00, 0x8b, 0x2d, 0x1c, 0x00, 0x00, 0x00, 0x66, 0x85, 0xc0, 0x0f,
  0x84, 0x93, 0x00, 0x00, 0x00, 0xc1, 0xe0, 0x05, 0x8d, 0x4c, 0x05, 0x14,
  0x83, 0xc5, 0x14, 0xeb, 0x0e, 0x8d, 0xb4, 0x26, 0x00, 0x00, 0x00, 0x00,
  0x83, 0xe9, 0x20, 0x39, 0xe9, 0x74, 0x79, 0x83, 0x79, 0xec, 0x01, 0x75,
  0xf3, 0x8b, 0x59, 0xfc, 0x8b, 0x71, 0xf4, 0x6b, 0x79, 0xf0, 0x34, 0x85,
  0xdb, 0x89, 0xf0, 0x74, 0x17, 0x29, 0xf7, 0x90, 0x0f, 0xb6, 0x14, 0x38,
  0x88, 0x10, 0x8b, 0x59, 0xfc, 0x83, 0xc0, 0x01, 0x89, 0xc2, 0x29, 0xf2,
  0x39, 0xd3, 0x77, 0xec, 0x3b, 0x19, 0x89, 0xc2, 0x74, 0x1b, 0x8d, 0xb6,
  0x00, 0x00, 0x00, 0x00, 0xc6, 0x02, 0x00, 0x8b, 0x59, 0xfc, 0x83, 0xc2,
  0x01, 0x8b, 0x31, 0x89, 0xd7, 0x29, 0xc7, 0x29, 0xde, 0x39, 0xf7, 0x72,
  0xeb, 0x83, 0xe3, 0x03, 0x74, 0xa6, 0xb8, 0x04, 0x00, 0x00, 0x00, 0x29,
  0xd8, 0x01, 0xd0, 0x90, 0x8d, 0x74, 0x26, 0x00, 0xc6, 0x02, 0x00, 0x83,
  0xc2, 0x01, 0x39, 0xc2, 0x75, 0xf6, 0x83, 0xe9, 0x20, 0x39, 0xe9, 0x75,
  0x8e, 0x8d, 0xb4, 0x26, 0x00, 0x00, 0x00, 0x00, 0xff, 0x15, 0x18, 0x00,
  0x00, 0x00, 0x31, 0xc0, 0x82, 0x83, 0xc4, 0x0c, 0x5b, 0x5e, 0x5f, 0x5d,
  0xc3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
  0x90, 0x90, 0x90, 0x90, 0x83, 0xec, 0x0c, 0xe8, 0x28, 0xff, 0xff, 0xff,
  0xb8, 0x01, 0x00, 0x00, 0x00, 0x82, 0x83, 0xc4, 0x0c, 0xc3, 0x00, 0x00,
  0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7a, 0x52, 0x00,
  0x01, 0x7c, 0x08, 0x01, 0x1b, 0x0c, 0x04, 0x04, 0x88, 0x01, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xac, 0xfe, 0xff, 0xff,
  0x24, 0x00, 0x00, 0x00, 0x00, 0x43, 0x0e, 0x0c, 0x47, 0x86, 0x03, 0x87,
  0x02, 0x59, 0xc7, 0xc6, 0x0e, 0x04, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
  0x3c, 0x00, 0x00, 0x00, 0xbc, 0xfe, 0xff, 0xff, 0x12, 0x00, 0x00, 0x00,
  0x00, 0x41, 0x0e, 0x08, 0x87, 0x02, 0x50, 0xc7, 0x0e, 0x04, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0xc0, 0xfe, 0xff, 0xff,
  0xc1, 0x00, 0x00, 0x00, 0x00, 0x41, 0x0e, 0x08, 0x85, 0x02, 0x41, 0x0e,
  0x0c, 0x87, 0x03, 0x41, 0x0e, 0x10, 0x86, 0x04, 0x41, 0x0e, 0x14, 0x83,
  0x05, 0x43, 0x0e, 0x20, 0x02, 0xb5, 0x0e, 0x14, 0x41, 0xc3, 0x0e, 0x10,
  0x41, 0xc6, 0x0e, 0x0c, 0x41, 0xc7, 0x0e, 0x08, 0x41, 0xc5, 0x0e, 0x04,
  0x14, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x54, 0xff, 0xff, 0xff,
  0x12, 0x00, 0x00, 0x00, 0x00, 0x43, 0x0e, 0x10, 0x4e, 0x0e, 0x04, 0x00
};
unsigned int loader_len = 492;
