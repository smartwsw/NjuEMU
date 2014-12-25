#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
make_helper(mov_cr_r) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 4);
	assert(m.mod == 3);
	switch (m.reg) {
		case 0 : reg_l(m.R_M) = cpu.CR0; 
				 print_asm("mov\t\t%%CR0,%%%s", regsl[m.R_M]);
				 break;
		default : assert (0);
	}
	return 2;
}

make_helper(mov_r_cr) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 4);
	assert(m.mod == 3);
	switch (m.reg) {
		case 0 : cpu.CR0 = reg_l(m.R_M);
				 print_asm("mov\t\t%%%s,%%CR0", regsl[m.R_M]);
				 break;
	}
	return 2;
}
