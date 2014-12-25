#include "exec/helper.h"
#include "cpu/modrm.h"

extern char suffix;

make_helper(lgdt_w) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch (m.opcode) {
		case 2: {
					swaddr_t addr;
					int len = read_ModR_M(eip + 1, &addr);
					cpu.GDTR.limit = swaddr_read(addr, 2);
					cpu.GDTR.base = swaddr_read(addr + 2, 4) & 0x00FFFFFF;
					print_asm("lgdt\t\t0x%x", addr);
					return 1 + len;
				}
		default :
				assert(0);
	}
}

make_helper(lgdt_l) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch (m.opcode) {
		case 2: {
					swaddr_t addr;
					int len = read_ModR_M(eip + 1, &addr);
					cpu.GDTR.limit = swaddr_read(addr, 2);
					cpu.GDTR.base = swaddr_read(addr + 2, 4);
					print_asm("lgdt\t\t0x%x", addr);
					return 1 + len;
				}
		default :
				assert(0);
	}
}

make_helper(lgdt_v) {
	return (suffix == 'l' ? lgdt_l(eip) : lgdt_w(eip));
}
