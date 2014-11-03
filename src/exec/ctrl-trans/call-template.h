#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(call_rel_, SUFFIX)) {
	DATA_TYPE_S addr = instr_fetch(eip + 1, DATA_BYTE);
	reg_l(R_ESP) -= DATA_BYTE;
	swaddr_write(reg_l(R_ESP), DATA_BYTE, eip + DATA_BYTE + 1);
	cpu.eip += addr;
#if DATA_BYTE == 2
	cpu.eip &= 0xffff;
#endif
	print_asm("call\t\t%x", cpu.eip + DATA_BYTE + 1);
	return DATA_BYTE + 1;
}
#include "exec/template-end.h"
