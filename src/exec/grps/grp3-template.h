#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

extern char suffix;

make_helper(concat(grp3_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	int result, len = 1;
	switch (m.opcode) {
		case 0 : {
					 DATA_TYPE imm;
					 cpu.OF = 0;
					 cpu.SF = 0;
					 if (m.mod == 3) {
						 int reg = REG(m.R_M);
						 imm = instr_fetch(eip + 1, DATA_BYTE);
						 result = reg & imm;
						 len += 1 + DATA_BYTE;
						 print_asm("test"str(SUFFIX)"\t\t%%%s,%d", REG_NAME(m.R_M) , imm);
					 }   
					 else {
						 swaddr_t addr;
						 len += read_ModR_M(eip + 1, &addr);
						 int right = swaddr_read(addr, DATA_BYTE);
						 imm = instr_fetch(eip + 1, DATA_BYTE);
						 len += DATA_BYTE;
						 result = right & imm; 
						 print_asm("test"str(SUFFIX)"\t\t%s,%d", ModR_M_asm , imm);
					 }   
					 return len;
				 }
		case 2: {
					if (m.mod == 3) {
						REG(m.R_M) = ~REG(m.R_M);
						len++;
						print_asm("not"str(SUFFIX)"\t\t%%%s", REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						DATA_TYPE tmp = swaddr_read(addr, DATA_BYTE);
						swaddr_write(addr, DATA_BYTE, ~tmp);
						print_asm("not"str(SUFFIX)"\t\t%s", ModR_M_asm);
					}
					return len;
				}
		case 3: {
					if (m.mod == 3) {
						cpu.CF = !!REG(m.R_M);
						result = -REG(m.R_M);
						cpu.OF = MSB(result) ^ MSB(REG(m.R_M));
						REG(m.R_M) = result;
						print_asm("neg\t\t%%%s",REG_NAME(m.R_M));
						len++;
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = -MEM_R(addr);
						cpu.CF = !!MEM_R(addr);
						cpu.OF = MSB(result) ^ MSB(MEM_R(addr));
						MEM_W(addr, result);
						print_asm("neg\t\t%s", ModR_M_asm);
					}
					return len;
				}
		case 4: {
					uint64_t result;
					if(m.mod == 3) {
						result = (uint64_t)REG(0) * (uint64_t)REG(m.R_M);
						REG(0) = result;
						cpu.CF = !!(result & 0xffffffff00000000);
						cpu.OF = cpu.CF;
						print_asm("mul\t\t%%%s", REG_NAME(m.R_M));
						return len + 1;
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = (uint64_t)REG(0) * (uint64_t)MEM_R(addr);
						REG(0) = result;
						cpu.CF = !!(result & 0xffffffff00000000);
						cpu.OF = cpu.CF;
						print_asm("mul\t\t%s", ModR_M_asm);
						return len;
					}
				}
		case 5: {
					int64_t result;
					if(m.mod == 3) {
						result = (int64_t)(DATA_TYPE_S)REG(0) * (int64_t)(DATA_TYPE_S)REG(m.R_M);
						if (suffix == 'b') {
							reg_w(R_AX) = result;
						}
						else {
							REG(R_EAX) = result;
							REG(R_EDX) = result >> (DATA_BYTE << 3);
						}
						cpu.CF = !!(result & 0xffffffff00000000);
						cpu.OF = cpu.CF;
						print_asm("imul\t\t%%%s", REG_NAME(m.R_M));
						return len + 1;
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = (int64_t)(DATA_TYPE_S)REG(0) * (int64_t)(DATA_TYPE_S)MEM_R(addr);
						REG(0) = result;
						cpu.CF = !!(result & 0xffffffff00000000);
						cpu.OF = cpu.CF;
						print_asm("imul\t\t%s", ModR_M_asm);
						return len;
					}
				}
		case 6: {
					DATA_TYPE result;
					DATA_TYPE rem;
					if (m.mod == 3) {
						result = REG(0) / REG(m.R_M);
						rem = REG(0) % REG(m.R_M);
						if (suffix == 'b') {
							reg_b(R_AL) = result;
							reg_b(R_AH) = rem;
						}
						else {
							REG(R_EAX) = result;
							REG(R_EDX) = rem;
						}
						print_asm("div\t\t%%%s", REG_NAME(m.R_M));
						return len + 1;
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = REG(0) / MEM_R(addr);
						rem = REG(0) % MEM_R(addr);
						if (suffix == 'b') {
							reg_b(R_AL) = result;
							reg_b(R_AH) = rem;
						}
						else {
							REG(R_EAX) = result;
							REG(R_EDX) = rem;
						}
						print_asm("div\t\t%s", ModR_M_asm);
						return len;
					}
				}
		case 7: {
					DATA_TYPE_S result;
					DATA_TYPE_S rem;
					if (m.mod == 3) {
						result = (DATA_TYPE_S)REG(0) / (DATA_TYPE_S)REG(m.R_M);
						rem = (DATA_TYPE_S)REG(0) % (DATA_TYPE_S)REG(m.R_M);
						if (suffix == 'b') {
							reg_b(R_AL) = result;
							reg_b(R_AH) = rem;
						}
						else {
							REG(R_EAX) = result;
							REG(R_EDX) = rem;
						}
						print_asm("idiv\t\t%%%s", REG_NAME(m.R_M));
						return len + 1;
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = (DATA_TYPE_S)REG(0) / (DATA_TYPE_S)MEM_R(addr);
						rem = (DATA_TYPE_S)REG(0) % (DATA_TYPE_S)MEM_R(addr);
						if (suffix == 'b') {
							reg_b(R_AL) = result;
							reg_b(R_AH) = rem;
						}
						else {
							REG(R_EAX) = result;
							REG(R_EDX) = rem;
						}
						print_asm("idiv\t\t%s", ModR_M_asm);
						return len;
					}
				}


		default :
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
	}
#include "exec/template-end.h"
