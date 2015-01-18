#include "exec/helper.h"
#include "movs.h"

extern char suffix;
extern int exec(swaddr_t);

make_helper(rep) {
	int len = 0;
	while (reg_l(R_ECX) > 0) {
		len = exec(eip + 1);
		reg_l(R_ECX)--;
	}
	switch (swaddr_read(cpu.eip + 1, 1)) {
		case 0xa4:
			print_asm("rep movsb");
			break;
		case 0xa5:
			print_asm("rep movs%c", suffix);
			break;
		case 0xaa:
			print_asm("rep stosb");
		case 0xab:
			print_asm("rep stos%c", suffix);
		default :
			printf("Invalid instruction with opcode %x at eip = 0x%x", instr_fetch(eip + 1, 1), eip);
			assert(0);
	}
	return len + 1;
}
