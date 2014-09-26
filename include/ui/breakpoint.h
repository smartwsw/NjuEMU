#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc
typedef struct breakpoint {
	int NO;
	struct breakpoint *next;
	bool if_used;
	int origin;
	/* TODO: Add more members if necessary */


} BP;

BP* new_bp();
#endif
