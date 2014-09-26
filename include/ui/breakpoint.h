#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc
typedef struct breakpoint {
	int NO;
	struct breakpoint *next;
	bool if_used;
	int origin;
	int addr;
	/* TODO: Add more members if necessary */


} BP;

BP* new_bp();
int find();
void load_bps();
void info_b();
#endif
