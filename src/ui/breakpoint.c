#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

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
		printf("No breakpoints now!\n");
		return;
	}
	BP *tmp=head;
	while(tmp!=NULL) {
		printf("Breakpoint %d at 0x%x.\n",tmp->NO,tmp->addr);
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
		i++;
		for (;i<NO;i++) {
			tmp_l=tmp;
			tmp=tmp->next;
			if(tmp==NULL) {
				printf("No breakpoint here!\n");
				return;
			}
		}
		swaddr_write(tmp->addr,1,tmp->origin);
		free_bp(tmp);
		tmp_l->next=tmp_l->next->next;
		return ;
	}
}
/* TODO: Implement the function of breakpoint */
