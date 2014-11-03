#include "exec/helper.h"
#include "cpu/modrm.h"

make_helper(concat(set, CC)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len;
	if(m.mod == 3) {
		reg_b(m.R_M) = COND;
		len = 2;
		print_asm("set"str(CC)"\t\t%%%s", regsb[m.R_M]);
	}
	else {
		swaddr_t addr;
		len = read_ModR_M(eip + 1, &addr) + 1;
		swaddr_write(addr, 1, COND);
		print_asm("set"str(CC)"\t\t%s", ModR_M_asm);
	}
	return len;
}
