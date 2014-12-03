#include "common.h"
#include "lib/misc.h"

#define INDEX_LEN 7
#define C_ADDR_LEN 6
#define TAG_LEN (27 - INDEX_LEN - C_ADDR_LEN)
typedef union {
	struct {
		uint32_t tag	: TAG_LEN;
		uint32_t index	: INDEX_LEN;
		uint32_t c_addr	: C_ADDR_LEN;
	};
	uint32_t addr;
} cache_addr;

typedef struct {
	bool valid;
	uint32_t tag;
	uint8_t data[64];
} block;

block l1_cache[128][8];

uint32_t l1cache_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	cache_addr temp;
	temp.addr = addr;
	int i;
//	if (((addr / 64 * 64 ) != ((addr + len) / 64 * 64)) ** (len > 1))
//		return dram_read(addr, len);
	for (i = 0; i < 8 ; i++){
		if (l1_cache[temp.index][i].valid)
			if (l1_cache[temp.index][i].tag == temp.tag)
				return 0;
//				return *(uint32_t *)(l1_cache[temp.index][i].data[temp.c_addr]);
	}
	for (i = 0; i < 8; i++) {
		if (!l1_cache[temp.index][i].valid) {
			l1_cache[temp.index][i].valid = true;
		}
	}
	return 0;
}
