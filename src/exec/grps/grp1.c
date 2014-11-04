#include "exec/helper.h"

#define DATA_BYTE 1
#include "grp1-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "grp1-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "grp1-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(grp1_v) {
	return (suffix == 'l' ? grp1_l(eip) : grp1_w(eip));
}
