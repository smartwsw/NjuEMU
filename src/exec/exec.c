#include "exec/helper.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	add_rm_r_b, add_rm_r_v, add_rm_r_b, add_rm_r_v, 
/* 0x04 */	inv, inv, inv, inv, 
/* 0x08 */	or_rm_r_b, or_rm_r_v, or_rm_r_b, or_rm_r_v, 
/* 0x0c */	or_i_a_b, or_i_a_v, inv, esc_code, 
/* 0x10 */	add_rm_r_b, add_rm_r_v, add_rm_r_b, add_rm_r_v, 
/* 0x14 */	add_i_a_b, add_i_a_v, inv, inv, 
/* 0x18 */	inv, inv, inv, inv, 
/* 0x1c */	inv, inv, inv, inv, 
/* 0x20 */	and_rm_r_b, add_rm_r_v, and_rm_r_b, and_rm_r_v, 
/* 0x24 */	and_i_a_b, and_i_a_v, inv, inv,
/* 0x28 */	cmp_rm_r_b, cmp_rm_r_v, cmp_rm_r_b, cmp_rm_r_v, 
/* 0x2c */	cmp_i_a_b, cmp_i_a_v, inv, inv, 
/* 0x30 */	inv, inv, inv, inv, 
/* 0x34 */	inv, inv, inv, inv,
/* 0x38 */	cmp_rm_r_b, cmp_rm_r_v, cmp_rm_r_b, cmp_rm_r_v, 
/* 0x3c */	cmp_i_a_b, cmp_i_a_v, inv, inv, 
/* 0x40 */	inv, inv, inv, inv, 
/* 0x44 */	inv, inv, inv, inv,
/* 0x48 */	inv, inv, inv, inv, 
/* 0x4c */	inv, inv, inv, inv, 
/* 0x50 */	push_r_v, push_r_v, push_r_v, push_r_v, 
/* 0x54 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x58 */	inv, inv, inv, inv, 
/* 0x5c */	inv, inv, inv, inv, 
/* 0x60 */	inv, inv, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	push_i_v, inv, push_i_b, inv, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	jo_b, jno_b, jb_b, jae_b,
/* 0x74 */	je_b, jne_b, jbe_b, ja_b,
/* 0x78 */	js_b, jns_b, jp_b, jnp_b, 
/* 0x7c */	jl_b, jge_b, jle_b, jg_b, 
/* 0x80 */	grp1_b, grp1_v, nemu_trap, grp1_v, 
/* 0x84 */	test_rm_r_b, test_rm_r_v, inv, inv, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv, lea_v, inv, inv, 
/* 0x90 */	inv, inv, inv, inv,
/* 0x94 */	inv, inv, inv, inv,
/* 0x98 */	inv, inv, inv, inv, 
/* 0x9c */	inv, inv, inv, inv, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	inv, inv, inv, inv,
/* 0xa8 */	test_a_i_b, test_a_i_v, inv, inv,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */	inv, inv, inv, ret,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	inv, inv, inv, inv,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, jcxz_b,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	call_rel_v, jmp_rel_v, inv, jmp_rel_b,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, inv,
/* 0xf4 */	inv, inv, grp3_b, grp3_v,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	cld, std, inv, push_m_v
};

make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}
