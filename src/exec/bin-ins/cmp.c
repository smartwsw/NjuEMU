#include "exec/helper.h"
#include "cpu/modrm.h"
extern char suffix;

make_helper(cmp_rm_imm_l) {
	int modrm = instr_fetch(eip + 1,1);
	int imm = instr_fetch(eip + 2,1);
	if ((modrm & 0xc0) == 0xc0) {
		int reg_code = modrm & 0x7;
		int reg_value = reg_l(reg_code);
		if (reg_value < imm) 
			cpu.CF = 1;
		int result = reg_value - imm;
		cpu.AF = 0;
		cpu.ZF = !!result;
		cpu.SF = (result >> 31) & 0x1;
		cpu.OF = 0;

		print_asm("cmp $0x%x,%%%s",imm,regsl[reg_code]);
		return 3;
	}
	else 
		assert(0);
}

make_helper(cmp_rm_imm_w) {
	int modrm = instr_fetch(eip + 1,1);
	int imm = instr_fetch(eip + 2,1);
	if ((modrm & 0xc0) == 0xc0) {
		int reg_code = modrm & 0x7;
		int reg_value = reg_w(reg_code);
		if (reg_value < imm) 
			cpu.CF = 1;
		int result = reg_value - imm;
		cpu.AF = 0;
		cpu.ZF = !!result;
		cpu.SF = (result >> 31) & 0x1;
		cpu.OF = 0;

		print_asm("cmp $0x%x,%%%s",imm,regsw[reg_code]);
		return 3;
	}
	else 
		assert(0);
}





make_helper(cmp_rm_imm_v) {
	return (suffix == 'l' ? cmp_rm_imm_l(eip) : cmp_rm_imm_w(eip));
}
