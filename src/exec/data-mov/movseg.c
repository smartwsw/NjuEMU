#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
make_helper(mov_cr_r) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 4);
	assert(m.mod == 3);
	switch (m.R_M) {
		case 0 : reg_l(m.reg) = cpu.CR0; 
				 printf("\e[33mTest!\e[0m\n");
				 print_asm("mov\t\t%%CR0,%%%s", regsl[m.reg]);
				 break;
		default : assert (0);
	}
	return 2;
}

make_helper(mov_r_cr) {
	ModR_M m;
				 Log("\e[33mTest3!\e[0m\n");
	m.val = instr_fetch(eip + 1, 4);
				 Log("\e[33mTest4!\e[0m\n");
	assert(m.mod == 3);
	switch (m.R_M) {
		case 0 : cpu.CR0 = reg_l(m.reg);
				 print_asm("mov\t\t%%%s,%%CR0", regsl[m.reg]);
				 Log("\e[33mTest2!\e[0m\n");
				 break;
		default : assert(0);
	}
	return 2;
}

make_helper(mov_rm_seg) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = 1;
	if (m.mod == 3) {
		int val = reg_w(m.R_M);
		switch (m.reg) {
			case 0 : cpu.ES.val = val;	
					 print_asm("mov\t\t%s,%%ES", regsw[m.R_M]);
					 break;
			case 1 : cpu.CS.val = val;
					 print_asm("mov\t\t%s,%%CS", regsw[m.R_M]);
					 break;
			case 2 : cpu.SS.val = val;
					 print_asm("mov\t\t%s,%%SS", regsw[m.R_M]);
					 break;
			case 3 : cpu.DS.val = val;	
					 print_asm("mov\t\t%s,%%DS", regsw[m.R_M]);
					 break;
			default : assert(0);
		}
		len = 2;
	}
	else assert(0);
	return len;
}

