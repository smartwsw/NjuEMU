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
	int i = elf->e_phnum;
	for(; i > 0; i ++) {
		if (ph[i].p_type == PT_LOAD) {
			int j;
			void* dst;
			const void* src;
			dst = (void*)ph[i].p_vaddr;
			src = (void*)(elf + ph[i].p_offset);
			for (j = 0; j < ph[i].p_filesz; j++) {
				*(char*)dst = *(char*)src;
				dst = (char*)dst + 1;
				src = (char*)src + 1;
			}
			for (j=0; j < ph[i].p_memsz - ph[i].p_filesz; j++) {
				*(char*)dst = 0;
				dst = (char*)dst + 1;
			}
			int tmp = ph[i].p_filesz % 4;
			if (!tmp)
				continue;
			else {
				int j;
				for (j = 0; j < 4 - tmp ; j++) {
					*(char*)dst = 0;
					dst = (char*)dst + 1;
				}
			}
		}
	}

	((void(*)(void)) elf->e_entry)();

	HIT_GOOD_TRAP;
}


