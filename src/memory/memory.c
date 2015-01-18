#include "common.h"
#include "nemu.h"

uint32_t current_sreg;
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t L1cache_read(hwaddr_t, size_t);
void L1cache_write(hwaddr_t, size_t, uint32_t);

/* Memory accessing interfaces */

lnaddr_t segment_translate(swaddr_t addr, int sreg_i) {
	lnaddr_t offset = 0;
	switch(sreg_i) {
		case 1:offset = (((uint32_t)cpu.CS.hide.base_31_24 )<< 24) + (((uint32_t)cpu.CS.hide.base_23_16)<< 16) + cpu.CS.hide.base_15_0;break; 
		case 0:offset = (((uint32_t)cpu.ES.hide.base_31_24 )<< 24) + (((uint32_t)cpu.ES.hide.base_23_16)<< 16) + cpu.ES.hide.base_15_0;break;
		case 2:offset = (((uint32_t)cpu.SS.hide.base_31_24 )<< 24) + (((uint32_t)cpu.SS.hide.base_23_16)<< 16) + cpu.SS.hide.base_15_0;break;
		case 3:offset = (((uint32_t)cpu.DS.hide.base_31_24 )<< 24) + (((uint32_t)cpu.DS.hide.base_23_16)<< 16) + cpu.DS.hide.base_15_0;break;
	}
	return addr + offset;
}

uint32_t page_translate(lnaddr_t addr) {
	if (cpu.PG) {
		uint32_t dir = (addr >> 22) & 0x3FF;
		uint32_t page = (addr >> 12) & 0x3FF;
		uint32_t offset = addr & 0xFFF;
		int* pos = (void*)(cpu.PDBR + dir);
		assert((*pos) & 0x1);
		int* pageaddr = (void*)((((*pos) >> 12) & 0xFFFFF) + page);
		assert((*pageaddr) &0x1);
		int* lnaddr = (void*)((((*pageaddr) >> 12) & 0xFFFFF) + offset);
		return *lnaddr;
	}
	else 
		return addr;
}
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return L1cache_read(addr, len);
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	L1cache_write(addr, len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	hwaddr_t hwaddr = page_translate(addr);
	return hwaddr_read(hwaddr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	hwaddr_t hwaddr = page_translate(addr);
	return hwaddr_write(hwaddr, len, data);
}
uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr = segment_translate(addr, current_sreg);
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr = segment_translate(addr, current_sreg);
	lnaddr_write(lnaddr, len, data);
}

//static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
//	assert(len == 1 || len == 2 || len == 4);
//	return dram_read(addr, len);
//}

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return swaddr_read(addr, len);
}

