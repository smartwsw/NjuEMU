#include "exec/helper.h"

#define DATA_BYTE 1
#include "xor-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "xor-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "xor-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(xor_i_a_v) {
	    return (suffix == 'l' ? xor_i_a_l(eip) : xor_i_a_w(eip));
}
make_helper(xor_rm_r_v) {
	    return (suffix == 'l' ? xor_rm_r_l(eip) : xor_rm_r_w(eip));
}
