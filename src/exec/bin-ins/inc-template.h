#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(inc_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE result = REG(reg_code) + 1;
	cpu.OF = ((result >> 31) & 0x1) ^ ((REG(reg_code) >> 31) & 0x1);
	cpu.SF = (result >> 31) &0x1;
	cpu.ZF = !result;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++)
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	REG(reg_code) = result;
	print_asm("inc\t\t%%%s", REG_NAME(reg_code));
	return 1;
}
make_helper(concat(dec_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE result = REG(reg_code) - 1;
	cpu.OF = ((result >> 31) & 0x1) ^ ((REG(reg_code) >> 31) & 0x1);
	cpu.SF = (result >> 31) &0x1;
	cpu.ZF = !result;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++)
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	REG(reg_code) = result;
	print_asm("dec\t\t%%%s", REG_NAME(reg_code));
	return 1;
}

#include "exec/template-end.h"
