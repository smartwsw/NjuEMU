#include "exec/helper.h"
#include "esccode.h"
#include "ui/ui.h"
#include "ui/breakpoint.h"
#include "nemu.h"

extern int stop_by_bp;
make_helper(inv) {
	/* invalid opcode */

	uint8_t temp[8];
	((uint32_t *)temp)[0] = instr_fetch(eip, 4);
	((uint32_t *)temp)[1] = instr_fetch(eip + 4, 4);
	printf("invalid opcode(eip = 0x%08x): %02x %02x %02x %02x %02x %02x %02x %02x ...\n", 
			eip, temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);

	assert(0);
}

make_helper(int3) {
	/* A breakpoint is hit! Do something here! */
	if (nemu_state==RUNNING) {
		printf("Hit breakpoint at 0x%x\n",cpu.eip);
		nemu_state=STOP;
	}
	int temp=find(cpu.eip);
	swaddr_write(cpu.eip,1,temp);
	cpu.eip--;
	stop_by_bp=1;
	return 1;
}

make_helper(nemu_trap) {
	printf("nemu: HIT \33[1;31m%s\33[0m TRAP at eip = 0x%08x\n\n", (cpu.eax == 0 ? "GOOD" : "BAD"), cpu.eip);
	nemu_state = END;

	print_asm("nemu trap");
	return 1;
}
make_helper(esc_code) {
	int len = 0;
	switch(instr_fetch(eip + 1, 1)) {
		case 0x80:	len = jo_v(eip + 1);		break;
		case 0x81:	len = jno_v(eip + 1);		break;
		case 0x82:	len = jb_v(eip + 1);		break;
		case 0x83:	len = jae_v(eip + 1);		break;
		case 0x84:	len = je_v(eip + 1);		break;
		case 0x85:	len = jne_v(eip + 1);		break;
		case 0x86:	len = jbe_v(eip + 1);		break;
		case 0x87:	len = ja_v(eip + 1);		break;
		case 0x88:	len = js_v(eip + 1);		break;
		case 0x89:	len = jns_v(eip + 1);		break;
		case 0x8a:	len = jp_v(eip + 1);		break;
		case 0x8b:	len = jnp_v(eip + 1);		break;
		case 0x8c:	len = jl_v(eip + 1);		break;
		case 0x8d:	len = jge_v(eip + 1);		break;
		case 0x8e:	len = jle_v(eip + 1);		break;
		case 0x8f:	len = jg_v(eip + 1);		break;
//		case 0x90:	len = seto(eip + 1);		break;
//		case 0x91:	len = setno(eip + 1);		break;
//		case 0x92:	len = setb(eip + 1);		break;
//		case 0x93:	len = setae(eip + 1);		break;
//		case 0x94:	len = sete(eip + 1);		break;
//		case 0x95:	len = setne(eip + 1);		break;
//		case 0x96:	len = setbe(eip + 1);		break;
//		case 0x97:	len = seta(eip + 1);		break;
//		case 0x98:	len = sets(eip + 1);		break;
//		case 0x99:	len = setns(eip + 1);		break;
//		case 0x9a:	len = setp(eip + 1);		break;
//		case 0x9b:	len = setnp(eip + 1);		break;
//		case 0x9c:	len = setl(eip + 1);		break;
//		case 0x9d:	len = setge(eip + 1);		break;
//		case 0x9e:	len = setle(eip + 1);		break;
//		case 0x9f:	len = setg(eip + 1);		break;
//		case 0xaf:	len = imul_r_rm_v(eip + 1);	break;
//		case 0xbe:	len = movsx_v(eip + 1);		break;
//		case 0xbf:	len = movsx_w2l(eip + 1);	break;
//		case 0xb6:	len = movzx_v(eip + 1);		break;
//		case 0xb7:	len = movzx_w2l(eip + 1);	break;
		default:	len = inv(eip);				break;
	}
	return 1 + len;
}
