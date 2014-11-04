#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(grp3_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	int result, len = 1;
	DATA_TYPE imm;
	switch (m.opcode) {
		case 0 : {
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
					 cpu.OF = 0;
					 cpu.CF = 0;
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
				}
		default :
				assert(0);

	}   
}
#include "exec/template-end.h"
