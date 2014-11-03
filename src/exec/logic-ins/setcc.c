#include "exec/helper.h"
#include "cpu/modrm.h"

#define CC a
#define COND (cpu.CF == 0) && (cpu.ZF == 0)
#include "setcc-template.h"
#undef COND
#undef CC

#define CC ae
#define COND !cpu.CF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC b
#define COND cpu.CF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC be
#define COND (cpu.CF || cpu.ZF)
#include "setcc-template.h"
#undef COND
#undef CC

#define CC e
#define COND cpu.ZF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC g
#define COND (!cpu.ZF && (cpu.SF == cpu.OF))
#include "setcc-template.h"
#undef COND
#undef CC

#define CC ge
#define COND (cpu.SF == cpu.OF)
#include "setcc-template.h"
#undef COND
#undef CC

#define CC l
#define COND (cpu.SF != cpu.OF)
#include "setcc-template.h"
#undef COND
#undef CC

#define CC le
#define COND (cpu.ZF || (cpu.OF != cpu.OF))
#include "setcc-template.h"
#undef COND
#undef CC

#define CC ne
#define COND !cpu.ZF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC no
#define COND !cpu.OF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC np
#define COND !cpu.PF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC ns
#define COND !cpu.SF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC o
#define COND cpu.OF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC p
#define COND cpu.PF
#include "setcc-template.h"
#undef COND
#undef CC

#define CC s
#define COND cpu.SF
#include "setcc-template.h"
#undef COND
#undef CC
