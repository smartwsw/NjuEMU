#include "exec/helper.h"
#include "cpu/modrm.h"
extern char suffix;

make_helper(test_rm_r_l) {
	int modrm=instr_fetch(eip+1,1);
	if ((modrm & 0xc0) == 0xc0) {
		int right = reg_l((modrm & 0x7));
		int left = reg_l((modrm >> 3) & 0x7);
		int result = left & right;
		cpu.OF = 0;
		cpu.CF = 0;
		cpu.SF = (result >> 31) & 0x1;
		cpu.ZF = !!result;
		bool parity = 1;
		int i;
		for (i = 0;i < 8;i++) 
			if (((result >> i) & 0x1) == 1)
				parity = ~parity;
		cpu.PF = parity;
		return 2;
	}
	else 
		assert (0);
		return 1;
}
make_helper(test_rm_r_w) {
	int modrm=instr_fetch(eip+1,1);
	if ((modrm & 0xc0) == 0xc0) {
		int right = reg_w((modrm & 0x7));
		int left = reg_w((modrm >> 3) & 0x7);
		int result = left & right;
		cpu.OF = 0;
		cpu.CF = 0;
		cpu.SF = (result >> 31) & 0x1;
		cpu.ZF = !!result;
		bool parity = 1;
		int i;
		for (i = 0;i < 8;i++) 
			if (((result >> i) & 0x1) == 1)
				parity = ~parity;
		cpu.PF = parity;
		return 2;
	}
	else 
		assert (0);
		return 1;
}






make_helper(test_rm_r_v) {
	return (suffix == 'l' ? test_rm_r_l(eip) : test_rm_r_w(eip));
}

