#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32
uint32_t expr(char *e, bool *success);
static BP bp_pool[NR_BP];
static BP *head, *free_;
static void add_to_tail(BP *bp) {
	BP *tmp=head;
	if (tmp==NULL) {
		head=bp;
		head->next=NULL;
		return;
	}
	while (tmp->next!=NULL)
		tmp=tmp->next;
	tmp->next=bp;
	bp->next=NULL;
}
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
	add_to_tail(new);
	return new;
}
void free_bp(BP *bp) {
	bp->if_used=false;
}
int find(int addr) {
	BP *temp=head;
	assert(temp!=NULL);
	while (temp!=NULL) {
		if (temp->addr==addr)
			break;
		temp=temp->next;
	}
	if (temp==NULL) {
		printf("failed\n");
		return 0;
	}
	return temp->origin;
}
void load_bps() {
	BP *tmp=head;
	while(tmp!=NULL) {
		swaddr_write(tmp->addr,1,0xcc);
		tmp=tmp->next;
	}
	return ;
}
void info_b() {
	if (head==NULL){
		printf("No breakpoints or watchpoint now!\n");
		return;
	}
	int count=1;
	BP *tmp=head;
	while(tmp!=NULL) {
		switch (tmp->type) {
			case 1: 
				printf("Breakpoint %d at 0x%x.\n",count,tmp->addr);
				break;
			case 2:
				printf("Watchpoint %d with current value %s = %u.\n",count,tmp->tokens,tmp->value);
				break;
		}
		count++;
		tmp=tmp->next;
	}
}
void delete_bp(int NO) {
	if (NO<1&&NO>32) 
		printf("Invalid breakpoint!\n");
	else {
		BP *tmp=head;
		if (tmp==NULL) {
			printf("No breakpoints now!\n");
			return;
		}
		int i=1;
		if (NO==1) {
			head=head->next;
			return;
		}
		BP *tmp_l=tmp;
		tmp=tmp->next;
		for (;i<NO;i++) {
			if(tmp==NULL) {
				printf("No breakpoint or watchpoint here!\n");
				return;
			tmp_l=tmp;
			tmp=tmp->next;
			}
		}
		swaddr_write(tmp->addr,1,tmp->origin);
		free_bp(tmp);
		tmp_l->next=tmp_l->next->next;
		return ;
	}
}
bool if_wp_changed() {
	BP *tmp=head;
	int value;
	bool success=true,if_changed=false;
	if (tmp==NULL)
		return false;
	else {
		while (tmp!=NULL) {
			if (head->type==2) {
				value=expr(tmp->tokens,&success);
				if (value!=tmp->value) {
					tmp->value=value;
					if_changed=true;
					printf("%s = %u",tmp->tokens,value);
				}
			}
			tmp=tmp->next;
		}
	}
	if(if_changed) printf("Hit watchpoint!\n");
	return if_changed;
}
/* TODO: Implement the function of breakpoint */
