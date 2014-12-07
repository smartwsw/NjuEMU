#define TAG_LEN (27 - INDEX_LEN - OFFSET_LEN)

#define HW_MEM_SIZE (128 * 1024 * 1024)

typedef union {
	struct {
		uint32_t offset	: OFFSET_LEN;
		uint32_t index	: INDEX_LEN;
		uint32_t tag	: TAG_LEN;
	};
	uint32_t addr;
} concat(Cache, _addr);

#define BLOCK_SIZE (1 << OFFSET_LEN)
#define INDEX_NUM (1 << INDEX_LEN)

typedef struct {
	uint8_t block[BLOCK_SIZE];
	uint32_t tag;
	bool valid;
#ifdef WRITE_BACK
	bool dirty;
#endif
} Cache[INDEX_NUM][LINE_NUM];

Cache cache;
void concat(init_, cache)() {
	int i = 0,j = 0;
	for (; i < LINE_NUM; i++)
		for (; j < INDEX_NUM; j++)
			cache[i][j].valid = false;
}

#define DATA_MASK 3
void concat(cache, _replace)(uint32_t index, int line, uint32_t tag) {
	int k = 0;
	concat(Cache, _addr) tmp;
	tmp.addr = 0;
	tmp.index = index;
#ifdef WRITE_BACK
	if (cache[index][line].valid && ccache[index][line].dirty) {
		tmp.tag = cache[index][line].tag;
		for (k = 0; k < BLOCK_SIZE; k++)
			next_write(tmp.addr + k, 1, cache[index][line].block[k]);
	}
	cache[index][line].dirty = false;
#endif
	tmp.tag = tag;
	for (k = 0; k < BLOCK_SIZE; k++)
		cache[index][line].block[k] = next_read(tmp.addr + k, 1);
	cache[index][line].tag = tag;
	cache[index][line].valid = true;
}

void concat(cache, _hwread)(hwaddr_t addr,  void* data) {
	test(addr < HW_MEM_SIZE, "addr = %x\n", addr);
	concat(Cache, _addr) tmp;
	tmp.addr = addr;
	uint32_t offset = tmp.offset;
	uint32_t index = tmp.index;
	uint32_t tag = tmp.tag;
	int i;
	for (i = 0; i < LINE_NUM; i++) 
		if (cache[index][i].valid && (cache[index][i].tag == tag))
			break;
	if (i == LINE_NUM) {
		i = rand() % LINE_NUM;
		concat(cache, _replace)(index, i, tag);
	}
	memcpy(data, cache[index][i].block + offset, 4);
}

void concat(cache, _hwwrite)(hwaddr_t addr, void* data, uint8_t *mask) {
	test(addr < HW_MEM_SIZE, "addr = %x\n", addr);
	concat(Cache, _addr) tmp;
	tmp.addr = addr & (~DATA_MASK);
	uint32_t offset = tmp.offset;
	uint32_t index = tmp.index;
	uint32_t tag = tmp.tag;
	int i;
	for (i = 0; i < LINE_NUM; i++) 
		if (cache[index][i].valid && (cache[index][i].tag == tag))
				break;
	if (i < LINE_NUM)
		memcpy_with_mask(cache[index][i].block + offset, data, 4, mask);
#ifdef WRITE_BACK
	if (i == LINE_NUM) {
		i = rand() % LINE_NUM;
		concat(cache, _replace)(index, i, tag);
		memcpy_with_mask(cache[index][i].block + offset, data, 4, mask);
	}
	cache[index][i].dirty = true;
#endif
}

uint32_t concat(cache, _read)(hwaddr_t addr, size_t len) {
//	printf("L1cache read at 0x%x\n", addr);
	assert ((len == 1) || (len == 2) || ( len == 4));
	uint32_t offset = addr & DATA_MASK;
	uint8_t tmp[8];
	concat(cache, _hwread)(addr, tmp);
	if ((addr ^ (addr + len - 1)) & (~DATA_MASK))
		concat(cache, _hwread)(addr + 4, tmp + 4);
	return *(uint32_t*)(tmp + offset) & (~0u >> ((4 - len) << 3));
}
void concat(cache, _write)(hwaddr_t addr, size_t len, uint32_t data) {
//	printf("L1cache write at 0x%x\n", addr);
	assert ((len == 1) || (len == 2) || ( len == 4));
	uint32_t offset = addr & DATA_MASK;
	uint8_t tmp[8];
	uint8_t mask[8];
	memset(mask, 0, 8);
	*(uint32_t*)(tmp + offset) = data;
	memset(mask + offset, 1, len);
	concat(cache, _hwwrite)(addr, tmp, mask);
	if ((addr ^ (addr + len + 1)) & (~DATA_MASK))
		concat(cache, _hwwrite)(addr + 4, tmp + 4, mask + 4);
#ifndef WRITE_BACK
	next_write(addr, len, data);
#endif
}
	
#undef OFFSET_LEN
#undef TAG_LEN
#undef SET_NUM


		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
