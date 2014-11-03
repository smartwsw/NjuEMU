#include "exec/helper.h"

#define DATA_BYTE 1
#include "cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmp-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(cmp_i_a_v) {
	    return (suffix == 'l' ? cmp_i_a_l(eip) : cmp_i_a_w(eip));
}
make_helper(cmp_rm_r_v) {
	    return (suffix == 'l' ? cmp_rm_r_l(eip) : cmp_rm_r_w(eip));
}
