#include "exec/helper.h"
#include "exec/template-start.h"
make_helper(concat(concat(concat(j, CC), _), SUFFIX)) {
	int32_t val = instr_fetch(eip + 1, DATA_BYTE);
	swaddr_t addr = cpu.eip;
	addr += val;
#if DATA_BYTE == 2
	addr &= 0xffff;
#endif
	if (COND) 
		cpu.eip = addr;
#if DATA_BYTE == 1
	print_asm("j"str(CC)"\t\t%x", addr + DATA_BYTE + 1);
#else 
	print_asm("j"str(CC)"\t\t%x", addr + DATA_BYTE + 2);
#endif
	return DATA_BYTE + 1;
}
#if DATA_BYTE == 4
extern char suffix;
make_helper(concat(concat(j, CC), _v)) {
	return (suffix == 'l' ? concat(concat(j, CC), _l)(eip) : concat(concat(j, CC), _w)(eip));
}
#endif
#include "exec/template-end.h"
