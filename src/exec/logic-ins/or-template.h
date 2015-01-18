#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(or_i_a_,SUFFIX)) {
	int imm = instr_fetch(eip + 1, DATA_BYTE);
	int result = REG(0) | imm;
	printf("\e[33mTest0!\e[0m\n");
	print_asm("or"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(0));
	REG(0) = result;
	cpu.ZF = !result;
	cpu.SF = (result >> 31) & 0x1;
	cpu.OF = 0;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++) 
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;	
	printf("\e[33mTest1!\e[0m\n");
	return DATA_BYTE + 1;
}
make_helper(concat(or_rm_r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int result, len = 1, opcode = instr_fetch(eip, 1);
	if(m.mod == 3) {
		int reg = REG(m.reg);
		int r_m = REG(m.R_M);
		result = r_m | reg;
		if (opcode == 0x08 || opcode == 0x09) {
			print_asm("or"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
			REG(m.reg) = result;
		}
		else {
			print_asm("or"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
			REG(m.R_M) = result;
		}
		len = 2;
	}
	else {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		int val = swaddr_read(addr, DATA_BYTE);
		int reg = REG(m.reg);
		if (opcode == 0x08 || opcode == 0x09) {
			result = val | reg;
			print_asm("or"str(SUFFIX)"\t\t%%%s,%s",REG_NAME(m.reg),ModR_M_asm);
			swaddr_write(addr, DATA_BYTE, result);
		}
		else {
			result = reg | val;
			print_asm("or"str(SUFFIX)"\t\t%s,%%%s",ModR_M_asm,REG_NAME(m.reg));
			REG(m.reg) = result;
		}
	}
	cpu.AF = 0;
	cpu.ZF = !result;
	cpu.SF = (result >> 31) & 0x1;
	cpu.OF = 0;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++) 
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	return len;
}

#include "exec/template-end.h"
