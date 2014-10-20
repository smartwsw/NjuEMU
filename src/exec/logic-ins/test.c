#include "exec/helper.h"
#include "cpu/modrm.h"
extern char suffix;

make_helper(test_rm_r_l) {
	int modrm=instr_fetch(eip+1,1);
	if ((modrm & 0xc0) == 0xc0) {
		int right_code = (modrm & 0x7);
		int left_code = (modrm >> 3) & 0x7;
		int right = reg_l(right_code);
		int left = reg_l(left_code);
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

		print_asm("test %%%s,%%%s", regsl[left_code] , regsl[right_code]);
		return 2;
	}
	else 
		assert (0);
		return 1;
}
make_helper(test_rm_r_w) {
	int modrm=instr_fetch(eip+1,1);
	if ((modrm & 0xc0) == 0xc0) {
		int right_code = (modrm & 0x7);
		int left_code = (modrm >> 3) & 0x7;
		int right = reg_w(right_code);
		int left = reg_w(left_code);
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

		print_asm("test %%%s,%%%s", regsw[left_code] , regsw[right_code]);
		return 2;
	}
	else 
		assert (0);
		return 1;
}






make_helper(test_rm_r_v) {
	return (suffix == 'l' ? test_rm_r_l(eip) : test_rm_r_w(eip));
}

