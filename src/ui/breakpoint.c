#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
		bp_pool[i].if_used=false;
	}
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
}
BP* new_bp() {
	BP *tmp=free_,*new;
	while(tmp->next->if_used==true) {
		tmp=tmp->next;
	}
	new=tmp->next;
	tmp->next=tmp->next->next;
	return new;
}
void free_bp(BP *bp) {
	bp->if_used=false;
	bp->next=bp_pool[bp->NO-1].next;
	bp_pool[bp->NO-1].next=bp;
}
/* TODO: Implement the function of breakpoint */
