#include "exec/helper.h"
#include "cpu/modrm.h"

make_helper(je_b) {
	int value = instr_fetch(eip+1,1);
	cpu.eip += value;
	return 2;
}
