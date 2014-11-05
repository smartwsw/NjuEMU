#include "prefix/prefix.h"

#include "data-mov/mov.h"

#include "data-mov/push.h"
#include "data-mov/pop.h"
#include "data-mov/xchg.h"
#include "misc/misc.h"
#include "misc/lea.h"
#include "logic-ins/test.h"
#include "logic-ins/setcc.h"
#include "logic-ins/and.h"
#include "logic-ins/or.h"
#include "logic-ins/xor.h"
#include "logic-ins/shift.h"
#include "ctrl-trans/jcc.h"
#include "ctrl-trans/call.h"
#include "ctrl-trans/jmp.h"
#include "ctrl-trans/ret.h"
#include "bin-ins/cmp.h"
#include "bin-ins/add.h"
#include "grps/grp1.h"
#include "grps/grp3.h"
#include "flag-ctrl/cld.h"
#include "string/movs.h"
#include "string/rep.h"
