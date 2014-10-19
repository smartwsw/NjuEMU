#include "exec/helper.h"
#include "cpu/modrm.h"
extern char suffix;

make_helper(push_r_l) {
	int reg_code = instr_fetch(eip,1) & 0x7;
	int value = reg_l(reg_code);
	cpu.esp = cpu.esp - 0x4;
	swaddr_write(cpu.esp,4,value);
	
	print_asm("push %%%s", regsl[reg_code]);
	return 1;
}
make_helper(push_r_w) {
	int reg_code = instr_fetch(eip,1) & 0x7;
	int value = reg_w(reg_code);
	cpu.esp = cpu.esp - 0x2;
	swaddr_write(cpu.esp,2,value);
	
	print_asm("push %%%s", regsw[reg_code]);
	return 1;
}











make_helper(push_r_v) {
	return (suffix == 'l' ? push_r_l(eip) : push_r_w(eip));
}
