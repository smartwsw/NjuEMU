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
make_helper(cmp_rm_i_v) {
	    return (suffix == 'l' ? cmp_rm_i_l(eip) : cmp_rm_i_w(eip));
}
make_helper(cmp_a_i_v) {
	    return (suffix == 'l' ? cmp_a_i_l(eip) : cmp_a_i_w(eip));
}
make_helper(cmp_rm_r_v) {
	    return (suffix == 'l' ? cmp_rm_r_l(eip) : cmp_rm_r_w(eip));
}
