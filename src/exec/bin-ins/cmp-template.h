#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(cmp_i_a_,SUFFIX)) {
	int imm = instr_fetch(eip + 2, DATA_BYTE);
	int opcode = instr_fetch(eip, 1);
	if(opcode == 0x1c || opcode == 0x1d)
		imm += cpu.CF;
	int result = REG(0) - imm;
	cpu.ZF = !result;
	cpu.SF = (result >> 31) & 0x1;
	cpu.OF = (MSB(concat(reg_, SUFFIX)(0)) != MSB(imm)) && (MSB(imm) == MSB(result));
	if(instr_fetch(eip, 1) == 0x2c || instr_fetch(eip, 1) == 0x2d) {
		REG(0) = result;
		if (opcode == 0x1c || opcode == 0x1d)
			print_asm("sbb"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(0));
		else 
			print_asm("sub"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(0));
	}
	else 
		print_asm("cmp"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(0));
	return DATA_BYTE + 1;
}
make_helper(concat(cmp_rm_r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int result, len = 1, opcode = instr_fetch(eip, 1);
	if(m.mod == 3) {
		int reg = REG(m.reg);
		int r_m = REG(m.R_M);
		if (opcode == 0x38 || opcode == 0x39 || opcode == 0x28 || opcode == 0x29 || opcode == 0x18 || opcode == 0x19) {
			if (opcode == 0x19 || opcode == 0x18)
				reg += cpu.CF;
			result = r_m - reg;
			cpu.CF = (r_m < reg);
			cpu.OF = (MSB(r_m) != MSB(reg)) && (MSB(reg) == MSB(result));
			if (opcode == 0x28 || opcode == 0x29 || opcode == 0x19 || opcode == 0x18) {
				REG(m.R_M) = result;
				if (opcode == 0x18 || opcode == 0x19)
					print_asm("sbb"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
				else
					print_asm("sub"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
			}
			else
				print_asm("cmp"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		}
		else {
			if (opcode == 0x1a || opcode == 0x1b)
				reg += cpu.CF;
			result = reg - r_m;
			cpu.CF = (reg < r_m);
			cpu.OF = (MSB(r_m) != MSB(reg)) && (MSB(r_m) == MSB(result));
			if (opcode == 0x2A || opcode == 0x2B || opcode == 0x1a || opcode == 0x1b) {
				REG(m.reg) = result;
				if (opcode == 0x1a || opcode == 0x1b)
					print_asm("sbb"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
				else 
					print_asm("sub"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
			}
			else 
				print_asm("cmp"str(SUFFIX)"\t\t%%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		}
		len = 2;
	}
	else {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		int val = swaddr_read(addr, DATA_BYTE);
		int reg = REG(m.reg);
		if (opcode == 0x38 || opcode == 0x39 || opcode == 0x28 || opcode == 0x29) {
			result = val - reg;
			cpu.OF = (MSB(val) != MSB(reg)) && (MSB(reg) == MSB(result));
			cpu.CF = (val < reg);
			if (opcode == 0x28 || opcode == 0x29) {
				swaddr_write(addr, DATA_BYTE, result);
				print_asm("sub"str(SUFFIX)"\t\t%%%s,%s",REG_NAME(m.reg), ModR_M_asm);
			}
			else 
				print_asm("cmp"str(SUFFIX)"\t\t%%%s,%s",REG_NAME(m.reg), ModR_M_asm);
		}
		else {
			result = reg - val;
			cpu.CF = (reg < val);
			cpu.OF = (MSB(val) != MSB(reg)) && (MSB(val) == MSB(result));
			if (opcode == 0x2a || opcode == 0x2b) {
				REG(m.reg) = result;
				print_asm("sub"str(SUFFIX)"\t\t%s,%%%s", ModR_M_asm,REG_NAME(m.reg));
			}
			else 
				print_asm("cmp"str(SUFFIX)"\t\t%s,%%%s", ModR_M_asm,REG_NAME(m.reg));
		}
	}
	cpu.ZF = !result;
	cpu.SF = (result >> 31) & 0x1;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++) 
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	return len;
}

#include "exec/template-end.h"
