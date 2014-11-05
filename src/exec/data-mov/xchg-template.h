#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(xchg_a_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	if (reg_code != R_EAX) {
		DATA_TYPE tmp = REG(R_EAX);
		REG(R_EAX) = REG(reg_code);
		REG(reg_code) = tmp;
		print_asm("xchg"str(SUFFIX)"\t\t%%%s,%%eax", REG_NAME(reg_code));
	}
	else 
		print_asm("nop");
	return 1;
}
make_helper(concat(xchg_rm_r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = 1;
	if(m.mod == 3) {
		DATA_TYPE tmp = REG(m.reg);
		len++;
		REG(m.reg) = REG(m.R_M);
		REG(m.R_M) = tmp;
		print_asm("xchg"str(SUFFIX)"\t\t%%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return len;
	}
	else {
		swaddr_t addr;
		len += read_ModR_M(eip + 1, &addr);
		DATA_TYPE tmp = swaddr_read(addr, DATA_BYTE);
		swaddr_write(addr, DATA_BYTE, REG(m.reg));
		REG(m.reg) = tmp;
		print_asm("xchg"str(SUFFIX)"\t\t%%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len;
	}
}

#include "exec/template-end.h"

