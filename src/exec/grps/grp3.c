#include "exec/helper.h"

#define DATA_BYTE 1
#include "grp3-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "grp3-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "grp3-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(grp3_v) {
	    return (suffix == 'l' ? grp3_l(eip) : grp3_w(eip));
}
