#include "nemu.h"
#include "lib/misc.h"
#include <stdlib.h>

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

#define OFFSET_LEN 6
#define INDEX_LEN 7
#define LINE_NUM 8
#define Cache L1Cache
#define cache L1cache
#define next_read dram_read
#define next_write dram_write
#include "cache-template.h"

void init_cache() {
	init_L1cache();
}
