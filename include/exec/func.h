#ifndef __FUNC_H__
#define __FUNC_H__
#include "common.h"

struct stack_frame {
	swaddr_t stack[1024];
	int top;
}
extern struct stack_frame func_stack;
swaddr_t current_func(swaddr_t);
char *func_name(swaddr_t);

#endif
