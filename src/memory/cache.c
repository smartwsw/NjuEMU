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

