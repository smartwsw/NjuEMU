#include <elf.h>
#include "trap.h"

void memcpy(void *dest, void *src, int size) {
	asm volatile("cld");
	asm volatile("rep movsl" : : "D"(dest), "S"(src), "c"(size));
}

void memset(void *dest, int value, int size) {
	asm volatile("cld");
	asm volatile("rep stosl" : : "D"(dest), "a"(value), "c"(size));
}

void loader() {
	Elf32_Ehdr *elf = (void *)0;
	Elf32_Phdr *ph = (void *)elf->e_phoff;
	int i = 0;
	for(; i < elf->e_phnum; i ++) {
		memcpy((void *)ph[i].p_vaddr, elf + ph[i].p_offset, ph[i].p_filesz);
	}

	((void(*)(void)) elf->e_entry)();

	HIT_GOOD_TRAP;
}


