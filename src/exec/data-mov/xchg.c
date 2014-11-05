#include "exec/helper.h"

#define DATA_BYTE 1
#include "xchg-template.h"
#undef DATA_BYTE 

#define DATA_BYTE 2
#include "xchg-template.h"
#undef DATA_BYTE 

#define DATA_BYTE 4
#include "xchg-template.h"
#undef DATA_BYTE 

extern char suffix;

make_helper(xchg_a_r_v) {
	return (suffix == 'l' ? xchg_a_r_l(eip) : xchg_a_r_w(eip));
}
make_helper(xchg_rm_r_v) {
	return (suffix == 'l' ? xchg_rm_r_l(eip) : xchg_rm_r_w(eip));
}
