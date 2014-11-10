#include "ui/ui.h"

#include "nemu.h"

#include <setjmp.h>

#define LOADER_START 0x100000

int exec(swaddr_t);
void load_prog();
void init_dram();
bool if_wp_changed();
void load_bps();
char assembly[40];
jmp_buf jbuf;	/* Make it easy to perform exception handling */

extern uint8_t loader [];
extern uint32_t loader_len;

extern int quiet;
extern int stop_by_bp;
void restart() {
	/* Perform some initialization to restart a program */
	load_prog();
	memcpy(hwa_to_va(LOADER_START), loader, loader_len);

	cpu.eip = LOADER_START;
	cpu.esp = 0x8000000;
	cpu.EFLAGS = 0x2;
	cpu.ebp = 0x0;

	init_dram();
}

static void print_bin_instr(swaddr_t eip, int len) {
	int i;
	printf("%8x:   ", eip);
	for(i = 0; i < len; i ++) {
		printf("%02x ", swaddr_read(eip + i, 1));
	}
	printf("%*.s", 50 - (12 + 3 * len), "");
}

void cpu_exec(volatile uint32_t n) {
	volatile uint32_t n_temp = n;

	setjmp(jbuf);
	int len;
	for(; n > 0; n --) {
		swaddr_t eip_temp = cpu.eip;
		int instr_len = exec(cpu.eip);

		cpu.eip += instr_len;

		len=instr_len;
		if(n_temp != -1 || (enable_debug && !quiet)) {
			print_bin_instr(eip_temp, instr_len);
			puts(assembly);
		}

		if (if_wp_changed()==true) { return; }
		if (stop_by_bp==2) {
			swaddr_write(cpu.eip-len,1,0xcc);
			stop_by_bp=0;
		}
		if(nemu_state == STOP) {
			if (stop_by_bp==1)
				stop_by_bp++;
			return; }
		if(nemu_state == INT) {
			printf("\n\nUser interrupt\n");
			return;
		} 
		else if(nemu_state == END) { 
			return; }
	}
}
