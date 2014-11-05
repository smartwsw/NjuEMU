#include "exec/helper.h"
#define DATA_BYTE 1

#define CC a
#define COND (!cpu.CF && !cpu.ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ae
#define COND (!cpu.CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC b
#define COND cpu.CF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC be
#define COND (cpu.ZF || cpu.CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC cxz
#define COND !reg_w(R_CX)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC e
#define COND cpu.ZF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC g
#define COND (!cpu.ZF && (cpu.SF == cpu.OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ge
#define COND (cpu.SF == cpu.OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC l
#define COND (cpu.SF != cpu.OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC le 
#define COND (cpu.ZF || (cpu.SF != cpu.OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ne
#define COND !cpu.ZF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC no
#define COND !cpu.OF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC np
#define COND !cpu.PF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ns
#define COND !cpu.SF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC o
#define COND cpu.OF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC p
#define COND cpu.PF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC s
#define COND cpu.SF
#include "jcc-template.h"
#undef COND
#undef CC
#undef DATA_BYTE



#define DATA_BYTE 2

#define CC a
#define COND (cpu.CF && cpu.ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ae
#define COND (!cpu.CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC b
#define COND cpu.CF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC be
#define COND (cpu.ZF || cpu.CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC cxz
#define COND !reg_w(R_CX)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC e
#define COND cpu.ZF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC g
#define COND (!cpu.ZF && (cpu.SF == cpu.OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ge
#define COND (cpu.SF == cpu.OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC l
#define COND (cpu.SF != cpu.OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC le 
#define COND (cpu.ZF || (cpu.SF != cpu.OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ne
#define COND !cpu.ZF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC no
#define COND !cpu.OF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC np
#define COND !cpu.PF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ns
#define COND !cpu.SF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC o
#define COND cpu.OF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC p
#define COND cpu.PF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC s
#define COND cpu.SF
#include "jcc-template.h"
#undef COND
#undef CC
#undef DATA_BYTE


#define DATA_BYTE 4

#define CC a
#define COND (cpu.CF && cpu.ZF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ae
#define COND (!cpu.CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC b
#define COND cpu.CF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC be
#define COND (cpu.ZF || cpu.CF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC cxz
#define COND !reg_w(R_CX)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC e
#define COND cpu.ZF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC g
#define COND (!cpu.ZF && (cpu.SF == cpu.OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ge
#define COND (cpu.SF == cpu.OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC l
#define COND (cpu.SF != cpu.OF)
#include "jcc-template.h"
#undef COND
#undef CC

#define CC le 
#define COND (cpu.ZF || (cpu.SF != cpu.OF))
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ne
#define COND !cpu.ZF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC no
#define COND !cpu.OF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC np
#define COND !cpu.PF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC ns
#define COND !cpu.SF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC o
#define COND cpu.OF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC p
#define COND cpu.PF
#include "jcc-template.h"
#undef COND
#undef CC

#define CC s
#define COND cpu.SF
#include "jcc-template.h"
#undef COND
#undef CC
#undef DATA_BYTE





