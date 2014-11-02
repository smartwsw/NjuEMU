#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(test_rm_r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	int result, len = 1;
	if (m.mod == 3) {
		int right = REG(m.R_M);
		int left = REG(m.reg);
		result = left & right;
		len++;
		print_asm("test\t%%%s,%%%s", REG_NAME(m.reg) , REG_NAME(m.R_M));
	}
	else {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		int left = REG(m.reg);
		int right = swaddr_read(addr, 4);
		result = right & left;
		print_asm("test\t%%%s,0x%x", REG_NAME(m.reg) , addr);
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
	return len;
}

make_helper(concat(test_rm_i_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	int result, len = 1;
	DATA_TYPE imm;
	switch (m.opcode) {
		case 0 : 
			if (m.mod == 3) {
				int reg = REG(m.R_M);
				imm = instr_fetch(eip + 1, DATA_BYTE);
				result = reg & imm;
				len += 1 + DATA_BYTE;
				print_asm("test\t%%%s,%d", REG_NAME(m.R_M) , imm);
			}
			else {
				swaddr_t addr;
				len += read_ModR_M(eip + 1, &addr);
				int right = swaddr_read(addr, 4);
				imm = instr_fetch(eip + 1, 4);
				len += DATA_BYTE;
				result = right & imm; 
				print_asm("test\t%d,0x%x", imm  , addr);
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
			return len;
		default :
			assert(0);

	}
}
#include "exec/template-end.h"

