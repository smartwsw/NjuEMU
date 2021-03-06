#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(add_i_a_,SUFFIX)) {
	int imm = instr_fetch(eip + 1, DATA_BYTE);
	int result = REG(0) + imm;
	if(instr_fetch(eip, 1) == 0x14 || instr_fetch(eip, 1) == 0x15) {
		result += cpu.CF;
		print_asm("adc"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(0));
	}
	else 
		print_asm("add"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(0));
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
	return DATA_BYTE + 1;
}
make_helper(concat(add_rm_r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int result, len = 1, opcode = instr_fetch(eip, 1);
	if(m.mod == 3) {
		int reg = REG(m.reg);
		int r_m = REG(m.R_M);
		if (opcode == 0x10 || opcode == 0x11 || opcode == 0x01 || opcode == 0x00) {
			result = r_m + reg;
			if (opcode == 0x11 || opcode == 0x10) {
				result += cpu.CF;
				print_asm("adc"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
			}
			else
				print_asm("add"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		REG(m.R_M) = result;
		}
		else {
			result = reg + r_m;
			if (opcode == 0x12 || opcode == 0x13) {
				result += cpu.CF;
				print_asm("adc"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
			}
			else 
				print_asm("add"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		REG(m.reg) = result;
		}
		len = 2;
	}
	else {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		int val = swaddr_read(addr, DATA_BYTE);
		int reg = REG(m.reg);
		if (opcode == 0x01 || opcode == 0x00 || opcode == 0x10 || opcode == 0x11) {
			result = val + reg;
			if (opcode == 0x11 || opcode == 0x10) {
				result += cpu.CF;
				print_asm("adc"str(SUFFIX)"\t\t%%%s,%s",REG_NAME(m.reg),ModR_M_asm);
			}
			else 
				print_asm("add"str(SUFFIX)"\t\t%%%s,%s",REG_NAME(m.reg),ModR_M_asm);
			swaddr_write(addr, DATA_BYTE, result);
		}
		else {
			result = reg + val;
			if (opcode == 0x10 || opcode == 0x11) {
				result += cpu.CF;
				print_asm("adc"str(SUFFIX)"\t\t%s,%%%s",ModR_M_asm,REG_NAME(m.reg));
			}
			else 
				print_asm("add"str(SUFFIX)"\t\t%s,%%%s",ModR_M_asm,REG_NAME(m.reg));
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
