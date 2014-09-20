#include "ui/ui.h"

#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int nemu_state = END;

void cpu_exec(uint32_t);
void restart();

/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

/* This function will be called when you press <C-c>. And it will return to 
 * where you press <C-c>. If you are interesting in how it works, please
 * search for "Unix signal" in the Internet.
 */
static void control_C(int signum) {
	if(nemu_state == RUNNING) {
		nemu_state = INT;
	}
}

void init_signal() {
	/* Register a signal handler. */
	struct sigaction s;
	memset(&s, 0, sizeof(s));
	s.sa_handler = control_C;
	int ret = sigaction(SIGINT, &s, NULL);
	assert(ret == 0);
}

static void cmd_c() {
	if(nemu_state == END) {
		puts("The Program does not start. Use 'r' command to start the program.");
		return;
	}

	nemu_state = RUNNING;
	cpu_exec(-1);
	if(nemu_state != END) { nemu_state = STOP; }
}

static void cmd_r() {
	if(nemu_state != END) { 
		char c;
		while(1) {
			printf("The program is already running. Restart the program? (y or n)");
			fflush(stdout);
			scanf(" %c", &c);
			switch(c) {
				case 'y': goto restart_;
				case 'n': return;
				default: puts("Please answer y or n.");
			}
		}
	}
restart_:
	restart();
	nemu_state = STOP;
	cmd_c();
}
static void cmd_si(volatile uint32_t n)
{
	if(nemu_state == STOP) {
		cpu_exec(n);
		if (nemu_state != END) { nemu_state = STOP; }
		return;
	}
	else {
		restart();
		nemu_state = STOP;
		cpu_exec(n);
		if (nemu_state != END) { nemu_state = STOP; }
		return;
	}
}
static void print_bin_instr(swaddr_t eip, int len) {
	    int i;
	    printf("%8x:   ", eip);
	    for(i = 0; i < len; i ++) {
	        printf("%02x ", swaddr_read(eip + i, 1));	
		}   
		printf("%*.s", 50 - (12 + 3 * len), "");
}
static void cmd_x(uint32_t para,uint32_t addr)
{
	int i;
	for (i=0;i<para;i++) {
		print_bin_instr(addr,1);
	}
}
void main_loop() {
	char *cmd;
	while(1) {
		cmd = rl_gets();
		char *p = strtok(cmd, " ");
		volatile uint32_t para=0,addr=0;
		if(p == NULL) {continue; }
		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r(); }
		else if(strcmp(p, "q") == 0) { return; }
		else if(strcmp(p, "si") == 0) { 
			p = strtok(NULL," ");
			if (p == NULL)
				para=1;
			else {
				para = atoi(p);
				if (para <= 0) {
					printf("Invalid parameter!");
					continue;
				}
			}
				printf("%d\n",para);
			cmd_si(para);
		}
		else if(strcmp(p, "info") == 0) {
			p = strtok(NULL," ");
			if (p == NULL)
				printf("Invalid parameter!\n");
			else {
				if (strcmp(p, "r") == 0) {
					printf("EAX      %p     %d\n",&cpu.eax,cpu.eax);
					printf("ECX      %p     %d\n",&cpu.ecx,cpu.ecx);
					printf("EDX      %p     %d\n",&cpu.edx,cpu.edx);
					printf("EBX      %p     %d\n",&cpu.ebx,cpu.ebx);
					printf("ESP      %p     %d\n",&cpu.esp,cpu.esp);
					printf("EBP      %p     %d\n",&cpu.ebp,cpu.ebp);
					printf("ESI      %p     %d\n",&cpu.esi,cpu.esi);
					printf("EDI      %p     %d\n",&cpu.edi,cpu.edi);
					printf("EIP      %p\n",&cpu.eip);
				}
				else {
					if (strcmp(p, "b") == 0) {
						printf("This function is not available now. \n");
						//Wait to set function "info b" here in future.
					}
					else {
						printf("Invalid parameter!\n");
					}
				}
			}
		}
		else if(strcmp(p, "x") ==0) {
			p = strtok(NULL," ");
			if (p == NULL) 
				printf("Invalid parameter!\n");
			else {
				sscanf(p,"%d",&para);
				printf("%d\n",para);
				p = strtok(NULL," ");
				sscanf(p,"%x",&addr);
				printf("%x\n",addr);
				cmd_x(para,addr);
			}
		}
		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
	}
}
