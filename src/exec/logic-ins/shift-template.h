#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(shift_rm_1_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE result = 0;
	int len = 1;
	switch (m.opcode) {
		case 4: {
					if (m.mod == 3) {
						result = REG(m.R_M) << 1;
						REG(m.R_M) = result;
						len++;
						cpu.CF = MSB(REG(m.R_M));
						print_asm("sal"str(SUFFIX)"\t\t$0x1,%%%s", REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = (swaddr_read(addr, DATA_BYTE)) << 1;
						swaddr_write(addr, DATA_BYTE, result);
						cpu.CF = MSB(swaddr_read(addr, DATA_BYTE));
						print_asm("sal"str(SUFFIX)"\t\t$0x1,%s", ModR_M_asm);
					}
					break;
				}
		case 5: {
					if (m.mod == 3) {
						result = (REG(m.R_M) >> 1) & ~(1 << ((DATA_BYTE << 3) - 1));
						cpu.OF = MSB(m.R_M);
						cpu.CF = REG(m.R_M) & 0x1;
						REG(m.R_M) = result;
						len++;
						print_asm("shr"str(SUFFIX)"\t\t$0x1,%%%s", REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = swaddr_read(addr, DATA_BYTE);
						cpu.OF = MSB(result);
						cpu.CF = result & 0x1;
						result = (result >> 1) & ~(1 << ((DATA_BYTE << 3) - 1));
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("shr"str(SUFFIX)"\t\t$0x1,%s", ModR_M_asm);
					}
					break;
				}
		case 7: {
					if (m.mod == 3) {
						result = REG(m.R_M) >> 1;
						cpu.OF = MSB(m.R_M);
						cpu.CF = REG(m.R_M) & 0x1;
						REG(m.R_M) = result;
						len++;
						print_asm("sar"str(SUFFIX)"\t\t$0x1,%%%s", REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = swaddr_read(addr, DATA_BYTE);
						cpu.OF = MSB(result);
						cpu.CF = result & 0x1;
						result = result >> 1;
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("sar"str(SUFFIX)"\t\t$0x1,%s", ModR_M_asm);
					}
					break;
				}
		default :
				printf("Invalid shift %x (eip = 0x%x)\n", m.opcode, cpu.eip);
				assert(0);
	}
	cpu.SF = (result >> 31) & 0x1;
	cpu.ZF = !result;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++)
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	return len;
}
make_helper(concat(shift_rm_c_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE result = 0;
	int len = 1;
	switch (m.opcode) {
		case 4: {
					if (m.mod == 3) {
						if (reg_b(R_CL)) 
							cpu.CF = REG(m.R_M) >> ((DATA_BYTE << 3) - reg_b(R_CL));
						else 
							cpu.CF = MSB(REG(m.R_M));
						result = REG(m.R_M) << reg_b(R_CL);
						REG(m.R_M) = result;
						len++;
						print_asm("sal"str(SUFFIX)"\t\t%%cl,%%%s", REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						if (reg_b(R_CL)) 
							cpu.CF = swaddr_read(addr, DATA_BYTE) >> ((DATA_BYTE << 3) - reg_b(R_CL));
						else 
							cpu.CF = MSB(swaddr_read(addr, DATA_BYTE));
						result = (swaddr_read(addr, DATA_BYTE)) << reg_b(R_CL);
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("sal"str(SUFFIX)"\t\t%%cl,%s", ModR_M_asm);
					}
					break;
				}
		case 5: {
					if (m.mod == 3) {
						if (reg_b(R_CL)) 
							cpu.CF = REG(m.R_M) >> ((DATA_BYTE << 3) - reg_b(R_CL));
						else 
							cpu.CF = MSB(REG(m.R_M));
						result = (REG(m.R_M) >> reg_b(R_CL)) & ~(1 << ((DATA_BYTE << 3) - 1));
						cpu.OF = MSB(m.R_M);
						cpu.CF = REG(m.R_M) & 0x1;
						REG(m.R_M) = result;
						len++;
						print_asm("shr"str(SUFFIX)"\t\t%%cl,%%%s", REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						if (reg_b(R_CL)) 
							cpu.CF = swaddr_read(addr, DATA_BYTE) >> ((DATA_BYTE << 3) - reg_b(R_CL));
						else 
							cpu.CF = MSB(swaddr_read(addr, DATA_BYTE));
						result = swaddr_read(addr, DATA_BYTE);
						cpu.OF = MSB(result);
						cpu.CF = result & 0x1;
						result = (result >> reg_b(R_CL)) & ~(1 << ((DATA_BYTE << 3) - 1));
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("shr"str(SUFFIX)"\t\t%%cl,%s", ModR_M_asm);
					}
					break;
				}
		case 7: {
					if (m.mod == 3) {
						if (reg_b(R_CL)) 
							cpu.CF = REG(m.R_M) >> ((DATA_BYTE << 3) - reg_b(R_CL));
						else 
							cpu.CF = MSB(REG(m.R_M));
						result = REG(m.R_M) >> reg_b(R_CL);
						cpu.OF = MSB(m.R_M);
						cpu.CF = REG(m.R_M) & 0x1;
						REG(m.R_M) = result;
						len++;
						print_asm("sar"str(SUFFIX)"\t\t%%cl,%%%s", REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						if (reg_b(R_CL)) 
							cpu.CF = swaddr_read(addr, DATA_BYTE) >> ((DATA_BYTE << 3) - reg_b(R_CL));
						else 
							cpu.CF = MSB(swaddr_read(addr, DATA_BYTE));
						result = swaddr_read(addr, DATA_BYTE);
						cpu.OF = MSB(result);
						cpu.CF = result & 0x1;
						result = result >> reg_b(R_CL);
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("sar"str(SUFFIX)"\t\t%%cl,%s", ModR_M_asm);
					}
					break;
				}

		default :
				printf("Invalid shift %x  (eip = 0x%x)\n", m.opcode, cpu.eip);
				assert(0);
	}
	cpu.SF = (result >> 31) & 0x1;
	cpu.ZF = !result;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++)
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	return len;
}
make_helper(concat(shift_rm_i_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE result = 0;
	uint8_t imm;
	int len = 2;
	switch (m.opcode) {
		case 4: {
					if (m.mod == 3) {
						imm = instr_fetch(eip + 2, 1) & 0x1f;
						if (imm) 
							cpu.CF = REG(m.R_M) >> ((DATA_BYTE << 3) - imm);
						else 
							cpu.CF = MSB(REG(m.R_M));
						result = REG(m.R_M) << imm;
						REG(m.R_M) = result;
						len++;
						print_asm("sal"str(SUFFIX)"\t\t$0x%x,%%%s", imm, REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						imm = instr_fetch(eip + len, 1) & 0x1f;
						if (imm) 
							cpu.CF = swaddr_read(addr, DATA_BYTE) >> ((DATA_BYTE << 3) - imm);
						else 
							cpu.CF = MSB(swaddr_read(addr, DATA_BYTE));
						result = (swaddr_read(addr, DATA_BYTE)) << imm;
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("sal"str(SUFFIX)"\t\t$0x%x,%s", imm, ModR_M_asm);
					}
					break;
				}
		case 5: {
					if (m.mod == 3) {
						imm = instr_fetch(eip + 2, 1) & 0x1f;
						if (imm) 
							cpu.CF = REG(m.R_M) >> ((DATA_BYTE << 3) - imm);
						else 
							cpu.CF = MSB(REG(m.R_M));
						result = (REG(m.R_M) >> imm) & ~(1 << ((DATA_BYTE << 3) - 1));
						cpu.OF = MSB(m.R_M);
						cpu.CF = REG(m.R_M) & 0x1;
						REG(m.R_M) = result;
						len++;
						print_asm("shr"str(SUFFIX)"\t\t$0x%x,%%%s", imm, REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						imm = instr_fetch(eip + len, 1) & 0x1f;
						if (imm) 
							cpu.CF = swaddr_read(addr, DATA_BYTE) >> ((DATA_BYTE << 3) - imm);
						else 
							cpu.CF = MSB(swaddr_read(addr, DATA_BYTE));
						result = swaddr_read(addr, DATA_BYTE);
						cpu.OF = MSB(result);
						cpu.CF = result & 0x1;
						result = (result >> imm) & ~(1 << ((DATA_BYTE << 3) - 1));
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("shr"str(SUFFIX)"\t\t$0x%x,%s", imm, ModR_M_asm);
					}
					break;
				}
		case 7: {
					if (m.mod == 3) {
						imm = instr_fetch(eip + 2, 1) & 0x1f;
						if (imm) 
							cpu.CF = REG(m.R_M) >> ((DATA_BYTE << 3) - imm);
						else 
							cpu.CF = MSB(REG(m.R_M));
						result = REG(m.R_M) >> imm;
						cpu.OF = MSB(m.R_M);
						cpu.CF = REG(m.R_M) & 0x1;
						REG(m.R_M) = result;
						len++;
						print_asm("sar"str(SUFFIX)"\t\t$0x%x,%%%s", imm, REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						imm = instr_fetch(eip + len, 1) & 0x1f;
						if (imm) 
							cpu.CF = swaddr_read(addr, DATA_BYTE) >> ((DATA_BYTE << 3) - imm);
						else 
							cpu.CF = MSB(swaddr_read(addr, DATA_BYTE));
						result = swaddr_read(addr, DATA_BYTE);
						cpu.OF = MSB(result);
						cpu.CF = result & 0x1;
						result = result >> imm;
						swaddr_write(addr, DATA_BYTE, result);
						print_asm("sar"str(SUFFIX)"\t\t$0x%x,%s", imm, ModR_M_asm);
					}
					break;
				}

		default :
				printf("Invalid shift %x (eip = 0x%x)\n", m.opcode, cpu.eip);
				assert(0);
	}
	cpu.SF = (result >> 31) & 0x1;
	cpu.ZF = !result;
	bool parity = 1;
	int i;
	for (i = 0;i < 8;i++)
		if (((result >> i) & 0x1) == 1)
			parity = ~parity;
	cpu.PF = parity;
	return len;
}
#include "exec/template-end.h"
