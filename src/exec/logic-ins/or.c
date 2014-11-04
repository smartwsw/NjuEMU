#include "exec/helper.h"

#define DATA_BYTE 1
#include "or-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "or-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "or-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(or_i_a_v) {
	    return (suffix == 'l' ? or_i_a_l(eip) : or_i_a_w(eip));
}
make_helper(or_rm_r_v) {
	    return (suffix == 'l' ? or_rm_r_l(eip) : or_rm_r_w(eip));
}
