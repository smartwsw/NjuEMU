#include "exec/helper.h"
#include "cpu/modrm.h"
extern char suffix;

make_helper(push_r_l) {
	int reg_code = instr_fetch(eip,1) & 0x7;
	printf("%x ",cpu.esp);
	cpu.esp = cpu.esp - 0x4;
	printf("%x ",cpu.esp);
	//swaddr_write(cpu.esp,4,reg_l(reg_code));
	
	print_asm("push $%%%s", regsl[reg_code]);
	return 1;
}
make_helper(push_r_w) {
	assert(0);
	return 0;
}











make_helper(push_r_v) {
	return (suffix == 'l' ? push_r_l(eip) : push_r_w(eip));
}
