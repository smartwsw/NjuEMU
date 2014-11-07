#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(pop_m_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = 1;
	if (m.opcode == 0) {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		swaddr_write(addr, DATA_BYTE, swaddr_read(reg_l(R_ESP), DATA_BYTE));
		reg_l(R_ESP) += DATA_BYTE;
	}
	else {
		printf("Invalid pop (eip = 0x%x)\n", eip);
		assert(0);
	}
	print_asm("pop"str(SUFFIX)"\t\t%s", ModR_M_asm);
	return len;
}
make_helper(concat(pop_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	reg_l(reg_code) = swaddr_read(reg_l(R_ESP), DATA_BYTE);
	reg_l(R_ESP) += DATA_BYTE;
	print_asm("pop"str(SUFFIX)"\t\t%%%s", concat(regs, SUFFIX)[reg_code]);
	return 1;
}
#include "exec/template-end.h"
