#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(jmp_rel_, SUFFIX)) {
	DATA_TYPE_S addr = instr_fetch(eip + 1, DATA_BYTE);
#if DATA_BYTE == 2
	addr &= 0xffff;
#endif
	cpu.eip += addr;
	
	print_asm("jmp\t\t%x", cpu.eip + DATA_BYTE + 1);
	return DATA_BYTE + 1;
}
#include "exec/template-end.h"
