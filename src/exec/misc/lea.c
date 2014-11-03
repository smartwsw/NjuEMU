#include "exec/helper.h"
#include "cpu/modrm.h"
make_helper(lea_l) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	swaddr_t addr;
	int len = read_ModR_M(eip + 1, &addr);
	reg_l(m.reg) = addr;
	print_asm("leal\t\t%s,%%%s", ModR_M_asm, regsl[m.reg]);
	return len + 1;
}
make_helper(lea_w) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	swaddr_t addr;
	int len = read_ModR_M(eip + 1, &addr);
	reg_w(m.reg) = addr;
	print_asm("leaw\t\t%s,%%%s", ModR_M_asm, regsw[m.reg]);
	return len + 1;
}

extern char suffix;

make_helper(lea_v) {
	return (suffix == 'l' ? lea_l(eip) : lea_w(eip));
}
