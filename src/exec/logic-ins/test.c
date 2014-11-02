#include "exec/helper.h"
#include "cpu/modrm.h"
extern char suffix;

make_helper(test_rm_r_l) {
	ModR_M modrm;
	modrm.val = instr_fetch(eip+1,1);
	int result;
	if (modrm.mod == 3) {
		int right_code = modrm.R_M;
		int left_code = modrm.reg;
		result = reg_l(left_code) & reg_l(right_code);
		print_asm("test %%%s,%%%s", regsl[left_code] , regsl[right_code]);
	}
	else {
		swaddr_t addr;
		read_ModR_M(eip + 1, &addr);
		int left_code = modrm.reg;
		int right = swaddr_read(addr, 4);
		result = right & reg_l(left_code);
		print_asm("test %%%s,0x%x", regsl[left_code] , addr);
	}
	cpu.OF = 0;
	cpu.CF = 0;
	cpu.SF = (result >> 31) & 0x1;
	cpu.ZF = !!result;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++) 
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	return 2;
}
make_helper(test_rm_r_w) {
	ModR_M modrm;
	modrm.val = instr_fetch(eip+1,1);
	int result;
	if (modrm.mod == 3) {
		int right_code = modrm.R_M;
		int left_code = modrm.reg;
		result = reg_w(left_code) & reg_w(right_code);
		print_asm("test %%%s,%%%s", regsw[left_code] , regsw[right_code]);
	}
	else {
		swaddr_t addr;
		read_ModR_M(eip + 1, &addr);
		int left_code = modrm.reg;
		int right = swaddr_read(addr, 4);
		result = right & reg_w(left_code);
		print_asm("test %%%s,0x%x", regsw[left_code] , addr);
	}
	cpu.OF = 0;
	cpu.CF = 0;
	cpu.SF = (result >> 31) & 0x1;
	cpu.ZF = !!result;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++) 
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	return 2;
}
make_helper(test_rm_r_b) {
	ModR_M modrm;
	modrm.val = instr_fetch(eip+1,1);
	int result;
	if (modrm.mod == 3) {
		int right_code = modrm.R_M;
		int left_code = modrm.reg;
		result = reg_b(left_code) & reg_b(right_code);
		print_asm("test %%%s,%%%s", regsb[left_code] , regsb[right_code]);
	}
	else {
		swaddr_t addr;
		read_ModR_M(eip + 1, &addr);
		int left_code = modrm.reg;
		int right = swaddr_read(addr, 4);
		result = right & reg_b(left_code);
		print_asm("test %%%s,0x%x", regsb[left_code] , addr);
	}
	cpu.OF = 0;
	cpu.CF = 0;
	cpu.SF = (result >> 31) & 0x1;
	cpu.ZF = !!result;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++) 
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	return 2;
}






make_helper(test_rm_r_v) {
	return (suffix == 'l' ? test_rm_r_l(eip) : test_rm_r_w(eip));
}

