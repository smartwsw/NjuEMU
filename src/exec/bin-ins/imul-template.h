#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(imul_r_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = 1;
	int64_t result;
	if(m.mod == 3) {
		result = (int64_t)(DATA_TYPE_S)REG(m.reg) * (int64_t)(DATA_TYPE_S)REG(m.R_M);
		REG(m.reg) = result;
		cpu.CF = !!(result & 0xffffffff00000000);
		cpu.OF = cpu.CF;
		print_asm("imul\t\t%%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return len + 1;
	}
	else {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		result = (int64_t)(DATA_TYPE_S)REG(m.reg) * (int64_t)(DATA_TYPE_S)MEM_R(addr);
		REG(m.reg) = result;
		cpu.CF = !!(result & 0xffffffff00000000);
		cpu.OF = cpu.CF;
		print_asm("imul\t\t%s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len;
	}
}

make_helper(concat(imul_r_rm_i_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE_S imm;
	int len = 1;
	int64_t result;
	if (m.mod == 3) {
		imm = instr_fetch(eip + 2, DATA_BYTE);
		result = (int64_t)(DATA_TYPE_S)REG(m.R_M) * (int64_t)imm;
		REG(m.reg) = result;
		cpu.CF = !!(result & 0xffffffff00000000);
		cpu.OF = cpu.CF;
		print_asm("imul\t\t$0x%x,%%%s,%%%s", imm, REG_NAME(m.reg), REG_NAME(m.reg));
		return len + 1 + DATA_BYTE;
	}
	else {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + len, DATA_BYTE);
		result = (int64_t)(DATA_TYPE_S)MEM_R(addr) * (int64_t)imm;
		REG(m.reg) = result;
		cpu.CF = !!(result & 0xffffffff00000000);
		cpu.OF = cpu.CF;
		print_asm("imul\t\t$0x%x,%s,%%%s", imm, ModR_M_asm, REG_NAME(m.reg));
		return len + DATA_BYTE;
	}
}

make_helper(concat(imul_r_rm_i8_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int8_t imm;
	int len = 1;
	int64_t result;
	if (m.mod == 3) {
		imm = instr_fetch(eip + 2, 1);
		result = (int64_t)(DATA_TYPE_S)REG(m.R_M) * (int64_t)imm;
		REG(m.reg) = result;
		cpu.CF = !!(result & 0xffffffff00000000);
		cpu.OF = cpu.CF;
		print_asm("imul\t\t$0x%x,%%%s,%%%s", imm, REG_NAME(m.reg), REG_NAME(m.reg));
		return len + 2;
	}
	else {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + len, 1);
		result = (int64_t)(DATA_TYPE_S)MEM_R(addr) * (int64_t)imm;
		REG(m.reg) = result;
		cpu.CF = !!(result & 0xffffffff00000000);
		cpu.OF = cpu.CF;
		print_asm("imul\t\t$0x%x,%s,%%%s", imm, ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

#include "exec/template-end.h"
