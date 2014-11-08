#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

extern char suffix;

make_helper(concat(push_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip,1) & 0x7;
	int value = REG(reg_code);
	cpu.esp = cpu.esp - DATA_BYTE;
	swaddr_write(cpu.esp,DATA_BYTE,value);
	print_asm("push"str(SUFFIX)"\t\t%%%s", REG_NAME(reg_code));
	return 1;
}
make_helper(concat(push_m_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	switch (m.opcode) {
		case 6 : {
					 swaddr_t addr;
					 int len = read_ModR_M(eip + 1, &addr);
					 cpu.esp -= DATA_BYTE;
					 int val = swaddr_read(addr, DATA_BYTE);
					 swaddr_write(cpu.esp, DATA_BYTE, val);
					 print_asm("push"str(SUFFIX)"\t\t0x%x", addr);
					 return len + 1;
				 }
		case 4: {
					if (m.mod == 3) {
						cpu.eip = (suffix == 'l') ? (REG(m.R_M) - 2) : ((REG(m.R_M) - 2) & 0xffff);
						print_asm("jmp\t\t%%%s", REG_NAME(m.R_M));
						return 2;
					}
					else {
						swaddr_t addr;
						int len = read_ModR_M(eip + 1, &addr) + 1;
						cpu.eip = (suffix == 'l') ? (MEM_R(addr) - 2) : ((MEM_R(addr) - 2) & 0xffff);
						print_asm("jmp\t\t%s", ModR_M_asm);
						return len;
					}
				}
		case 2: {
					int len = 1;
					reg_l(R_ESP) -= DATA_BYTE;
					MEM_W(reg_w(R_ESP), cpu.eip);
					if(m.mod == 3) {
						if (suffix == 'w') 
							cpu.eip = (REG(m.R_M) & 0xffff) - 2;
						else
							cpu.eip = REG(m.R_M) - 2;
						print_asm("call\t\t%%%s", REG_NAME(m.R_M));
					}
					else {
						swaddr_t addr;
						int len = read_ModR_M(eip + 1, &addr);
						if (suffix == 'w')
							cpu.eip = (MEM_R(addr) & 0xffff) - len - 1;
						else 
							cpu.eip = MEM_R(addr) - len - 1;
						print_asm("call\t\t%s", ModR_M_asm);
					}
					return len + 1;
				}
		case 0: {
					if(m.mod == 3) {
						REG(m.R_M)++;
						print_asm("inc\t\t%%%s", REG_NAME(m.R_M));
						return 2;
					}
					else {
						swaddr_t addr;
						int len = read_ModR_M(eip + 1, &addr);
						DATA_TYPE_S tmp = MEM_R(addr);
						tmp++;
						MEM_W(addr, tmp);
						print_asm("inc\t\t%s", ModR_M_asm);
						return len + 1;
					}
				}
		default :
				 assert(0);
	}
}
make_helper(concat(push_i_,SUFFIX)) {
	int imm = instr_fetch(eip + 1, DATA_BYTE);
	cpu.esp -= DATA_BYTE;
	swaddr_write(cpu.esp, DATA_BYTE, imm);
	print_asm("push"str(SUFFIX)"\t\t%d", imm);
	return DATA_BYTE + 1;
}
#include "exec/template-end.h"
