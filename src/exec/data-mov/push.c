#include "exec/helper.h"
make_helper(push_r_v) {
	int opcode=swaddr_read(eip,1);
	int reg_type=opcode&7;
	printf("%d\n",reg_l(reg_type));
	return 1;
}
