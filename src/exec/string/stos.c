#include "exec/helper.h"
#include "stos.h"

extern char suffix;

make_helper(stos_b) {
	cpu.edi = reg_b(R_AL);
	cpu.ES.val = 0;
	if (cpu.DF)
		reg_b(R_AL)++;
	else
		reg_b(R_AL)--;
	return 1;
}

make_helper(stos_w) {
	cpu.edi = reg_w(R_AX);
	cpu.ES.val = 0;
	if (cpu.DF)
		reg_w(R_AX) += 2;
	else 
		reg_w(R_AX) -= 2;
	return 1;
}

make_helper(stos_l) {
	cpu.edi = reg_l(R_EAX);
	cpu.ES.val = 0;
	if (cpu.DF)
		reg_l(R_EAX) += 4;
	else 
		reg_l(R_EAX) -= 4;
	return 1;
}

make_helper(stos_v) {
	return (suffix == 'l' ? stos_l(eip) : stos_w(eip));
}
