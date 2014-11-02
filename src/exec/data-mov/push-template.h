#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(push_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip,1) & 0x7;
	int value = REG(reg_code);
	cpu.esp = cpu.esp - 0x4;
	swaddr_write(cpu.esp,4,value);
	print_asm("push %%%s", REG_NAME(reg_code));
	return 1;
}
#include "exec/template-end.h"
