#include "exec/helper.h"

#define DATA_BYTE 1
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "add-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "add-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(add_i_a_v) {
	    return (suffix == 'l' ? add_i_a_l(eip) : add_i_a_w(eip));
}
make_helper(add_rm_r_v) {
	    return (suffix == 'l' ? add_rm_r_l(eip) : add_rm_r_w(eip));
}
