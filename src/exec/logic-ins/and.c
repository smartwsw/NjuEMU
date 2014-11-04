#include "exec/helper.h"

#define DATA_BYTE 1
#include "and-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "and-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "and-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(and_i_a_v) {
	    return (suffix == 'l' ? and_i_a_l(eip) : and_i_a_w(eip));
}
make_helper(and_rm_r_v) {
	    return (suffix == 'l' ? and_rm_r_l(eip) : and_rm_r_w(eip));
}
