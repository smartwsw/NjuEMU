#include "exec/helper.h"

extern char suffix;

make_helper(ret) {
	int opcode = instr_fetch(eip, 1);
	if(suffix == 'l') {
		cpu.eip = swaddr_read(reg_l(R_ESP), 4) - 1;
		reg_l(R_ESP) += 4;
	}
	else {
		cpu.eip = swaddr_read(reg_l(R_ESP), 2) - 1;
		reg_l(R_ESP) += 2;
	}
	if (opcode == 0xc2)
		cpu.esp += instr_fetch(eip + 1, 2);
	print_asm("ret");
	return 1;
}

