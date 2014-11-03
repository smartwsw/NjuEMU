#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(grp1_, SUFFIX)) {
	ModR_M m;
	int opcode = instr_fetch(eip, 1); 
	m.val = instr_fetch(eip + 1,1);
	int len = 1, result;
	int imm, value;
	swaddr_t addr;
	if (opcode == 0x83) {
		imm = instr_fetch(eip + 2,1);
		//imm = (imm << 24) >> 24; 
		len += 2;
	}   
	else {
		imm = instr_fetch(eip + 2, DATA_BYTE);
		len += DATA_BYTE + 1;
	}   
	if (m.mod == 3) 
		value = REG(m.R_M);
	else {
		len += read_ModR_M(eip + 1, &addr) - 1;
		value = swaddr_read(addr, 1); 
	}   
	switch (m.opcode) {
		case 7 : { 
					 result = value - imm;
					 if (value < imm)
						 cpu.CF = 1;
					 if (m.mod == 3)
						 print_asm("cmp"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(m.R_M));
					 else
						 print_asm("cmp"str(SUFFIX)"\t\t$0x%x,0x%x",imm, addr);
					 break;
				 }   
		case 5 : { 
					 result = value - imm;
					 if (value < imm)
						 cpu.CF = 1;
					 if (m.mod == 3) {
						 REG(m.R_M) = result;
						 print_asm("sub"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(m.R_M));
					 }
					 else {
						 swaddr_write(addr, DATA_BYTE, result);
						 print_asm("sub"str(SUFFIX)"\t\t$0x%x,0x%x",imm, addr);
					 }
					 break;
				 }
		case 0: {
					result = value + imm;
					cpu.CF = ((value >> 31) & 0x1) && ((imm >> 31) & 0x1); 
					if (m.mod == 3) {
						REG(m.reg) = result;
						print_asm("add"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(m.reg));
					}
					else {
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("add"str(SUFFIX)"\t\t$0x%x,0x%x",imm, addr);
					}
					break;
				}
		case 2: {
					result = value + imm + cpu.CF;
					cpu.CF = ((value >> 31) & 0x1) && ((imm >> 31) & 0x1); 
					if (m.mod == 3) {
						REG(m.reg) = result;
						print_asm("add"str(SUFFIX)"\t\t$0x%x,%%%s",imm,REG_NAME(m.reg));
					}
					else {
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("add"str(SUFFIX)"\t\t$0x%x,0x%x",imm, addr);
					}
					break;
				}

		default :
				assert(0);
	}
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
