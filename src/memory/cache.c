#include "nemu.h"
#include "lib/misc.h"
#include <stdlib.h>

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

#define OFFSET_LEN 6
#define INDEX_LEN 12
#define LINE_NUM 16
#define Cache L2Cache
#define cache L2cache
#define next_read dram_read
#define next_write dram_write
//#define WRITE_BACK
#include "cache-template.h"
//#undef WRTIE_BACK

#define OFFSET_LEN 6
#define INDEX_LEN 7
#define LINE_NUM 8
#define Cache L1Cache
#define cache L1cache
#define next_read L2cache_read
#define next_write L2cache_write
#include "cache-template.h"

void init_cache() {
	init_L1cache();
	init_L2cache();
}
