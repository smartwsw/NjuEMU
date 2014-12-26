#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(jmp_rel_, SUFFIX)) {
	DATA_TYPE_S addr = instr_fetch(eip + 1, DATA_BYTE);
	cpu.eip += addr;
#if DATA_BYTE == 2
	cpu.eip &= 0xffff;
#endif
	
	print_asm("jmp\t\t%x", cpu.eip + DATA_BYTE + 1);
	return DATA_BYTE + 1;
}

make_helper(concat(jmp_ptr_, SUFFIX)) {
	DATA_TYPE_S addr = instr_fetch(eip + 1, DATA_BYTE);
	cpu.eip = addr;
#if DATA_BYTE == 2
	cpu.eip &= 0xffff;
#endif
	uint16_t imm = instr_fetch(eip + 1 + DATA_BYTE, 2);
	cpu.CS.val = imm;
	print_asm("jmp\t\t$0x%x,%x", imm, addr);
	return 0;
}
#include "exec/template-end.h"
