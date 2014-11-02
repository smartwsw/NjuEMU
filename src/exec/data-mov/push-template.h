#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(push_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip,1) & 0x7;
	int value = REG(reg_code);
	cpu.esp = cpu.esp - DATA_BYTE;
	swaddr_write(cpu.esp,DATA_BYTE,value);
	print_asm("push"str(SUFFIX)"\t%%%s", REG_NAME(reg_code));
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
					 print_asm("push"str(SUFFIX)"\t0x%x", addr);
					 return len + 1;
				 }
		default :
				 assert(0);
	}
}
#include "exec/template-end.h"
