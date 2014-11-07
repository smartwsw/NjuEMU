#include "exec/helper.h"
#include "cpu/modrm.h"

extern char suffix;

make_helper(movx_b_l) {
	ModR_M m;
	bool mod;
	if (instr_fetch(eip, 1) == 0xbe || instr_fetch(eip, 1) == 0xbf)
		mod = 1;
	else 
		mod = 0;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3){
		reg_l(m.reg) = mod ? (int32_t)(int8_t)reg_b(m.R_M) : (uint32_t)reg_b(m.R_M);
		if (mod)
			print_asm("movsx\t\t%%%s,%%%s",regsb[m.R_M], regsl[m.reg]);
		else
			print_asm("movzx\t\t%%%s,%%%s",regsb[m.R_M], regsl[m.reg]);
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr) + 1;
		reg_l(m.reg) = mod ? (int32_t)(int8_t)swaddr_read(addr, 1) : (uint32_t)swaddr_read(addr, 1);
		if (mod)
			print_asm("movsx\t\t%s,%%%s", ModR_M_asm, regsl[m.reg]);
		else
			print_asm("movzx\t\t%s,%%%s", ModR_M_asm, regsl[m.reg]);
		return len;
	}
}
make_helper(movx_b_w) {
	ModR_M m;
	bool mod;
	if (instr_fetch(eip, 1) == 0xbe || instr_fetch(eip, 1) == 0xbf)
		mod = 1;
	else 
		mod = 0;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3){
		reg_l(m.reg) = mod ? (int16_t)(int8_t)reg_w(m.R_M) : (uint16_t)reg_w(m.R_M);
		if (mod)
			print_asm("movsx\t\t%%%s,%%%s",regsb[m.R_M], regsw[m.reg]);
		else
			print_asm("movzx\t\t%%%s,%%%s",regsb[m.R_M], regsw[m.reg]);
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr) + 1;
		reg_l(m.reg) = mod ? (int16_t)(int8_t)swaddr_read(addr, 1) : (uint16_t)swaddr_read(addr, 1);
		if (mod)
			print_asm("movsx\t\t%s,%%%s", ModR_M_asm, regsw[m.reg]);
		else
			print_asm("movzx\t\t%s,%%%s", ModR_M_asm, regsw[m.reg]);
		return len;
	}
}
make_helper(movx_w_l) {
	ModR_M m;
	bool mod;
	if (instr_fetch(eip, 1) == 0xbe || instr_fetch(eip, 1) == 0xbf)
		mod = 1;
	else 
		mod = 0;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod == 3){
		reg_l(m.reg) = mod ? (int32_t)(int16_t)reg_w(m.R_M) : (uint32_t)reg_w(m.R_M);
		if (mod)
			print_asm("movsx\t\t%%%s,%%%s",regsw[m.R_M], regsl[m.reg]);
		else
			print_asm("movzx\t\t%%%s,%%%s",regsw[m.R_M], regsl[m.reg]);
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr) + 1;
		reg_l(m.reg) = mod ? (int32_t)(int16_t)swaddr_read(addr, 1) : (uint32_t)swaddr_read(addr, 1);
		if (mod)
			print_asm("movsx\t\t%s,%%%s", ModR_M_asm, regsl[m.reg]);
		else
			print_asm("movzx\t\t%s,%%%s", ModR_M_asm, regsl[m.reg]);
		return len;
	}
}
make_helper(movx_v) {
	return (suffix == 'l' ? movx_b_l(eip) : movx_w_l(eip));
}
