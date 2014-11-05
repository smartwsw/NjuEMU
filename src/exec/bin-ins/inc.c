#include "exec/helper.h"
#include "cpu/modrm.h"
extern char suffix;

#define DATA_BYTE 2
#include "inc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "inc-template.h"
#undef DATA_BYTE


make_helper(inc_dec_rm_b) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	uint8_t result = 0;
	int len = 1;
	switch (m.opcode) {
		case 0: {
					if (m.mod == 3) {
						result = reg_b(m.R_M) + 1;
						cpu.OF = ((result >> 31) & 0x1) ^ ((reg_b(m.R_M) >> 31) & 0x1);
						cpu.SF = (result >> 31) &0x1;
						cpu.ZF = !result;
						bool parity = 1;
						int i;
						for (i = 0;i < 8;i++)
							if (((result >> i) & 0x1) == 1)
								parity = ~parity;
						cpu.PF = parity;
						reg_b(m.R_M) = result;
						print_asm("inc\t\t%%%s", regsb[m.R_M]);
						return len + 1;
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = swaddr_read(addr, 1) + 1;
						cpu.OF = ((result >> 31) & 0x1) ^ ((swaddr_read(addr, 1) >> 31) & 0x1);
						cpu.SF = (result >> 31) & 0x1;
						cpu.ZF = !result;
						bool parity = 1;
						int i;
						for (i = 0;i < 8;i++)
							if (((result >> i) & 0x1) == 1)
								parity = ~parity;
						cpu.PF = parity;
						swaddr_write(addr, 1, result);
						print_asm("inc\t\t%s", ModR_M_asm);
						return len;
					}
				}
		case 1: {
					if (m.mod == 3) {
						result = reg_b(m.R_M) - 1;
						cpu.OF = ((result >> 31) & 0x1) ^ ((reg_b(m.R_M) >> 31) & 0x1);
						cpu.SF = (result >> 31) &0x1;
						cpu.ZF = !result;
						bool parity = 1;
						int i;
						for (i = 0;i < 8;i++)
							if (((result >> i) & 0x1) == 1)
								parity = ~parity;
						cpu.PF = parity;
						reg_b(m.R_M) = result;
						print_asm("inc\t\t%%%s", regsb[m.R_M]);
						return len + 1;
					}
					else {
						swaddr_t addr;
						len += read_ModR_M(eip + 1, &addr);
						result = swaddr_read(addr, 1) - 1;
						cpu.OF = ((result >> 31) & 0x1) ^ ((swaddr_read(addr, 1) >> 31) & 0x1);
						cpu.SF = (result >> 31) & 0x1;
						cpu.ZF = !result;
						bool parity = 1;
						int i;
						for (i = 0;i < 8;i++)
							if (((result >> i) & 0x1) == 1)
								parity = ~parity;
						cpu.PF = parity;
						swaddr_write(addr, 1, result);
						print_asm("inc\t\t%s", ModR_M_asm);
						return len;
					}
				}
		default :
				printf("Invalid opcode at eip 0x%x", eip);
				assert(0);
	}
}
make_helper(inc_r_v) {
	return (suffix == 'l' ? inc_r_l(eip) : inc_r_w(eip));
}
make_helper(dec_r_v) {
	return (suffix == 'l' ? dec_r_l(eip) : dec_r_w(eip));
}

