#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"
#include "nemu.h"
#define INT3_CODE 0xcc
typedef struct token {
	int type;
	char str[32];
} Token;
typedef struct breakpoint {
	int NO;
	struct breakpoint *next;
	bool if_used;
	int origin;
	int addr;
	int type;
	char tokens[100];
	int value;
	/* TODO: Add more members if necessary */


} BP;

BP* new_bp();
int find();
void load_bps();
void info_b();
void delete_bp(int NO);
#endif
