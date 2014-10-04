#include "ui/ui.h"
#include "ui/breakpoint.h"
#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int nemu_state = END;
int stop_by_bp=0;
void cpu_exec(uint32_t);
void restart();
uint32_t expr(char *e, bool *success);
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
	load_bps();
	nemu_state = STOP;
	cmd_c();
}
static void cmd_si(volatile uint32_t n)
{
	if (nemu_state == END){
		restart();
		load_bps();
		nemu_state = RUNNING;
		cpu_exec(n);
		if (nemu_state != END) { nemu_state = RUNNING; }
		return;
	}
	else {
		cpu_exec(n);
		if (nemu_state != END) { nemu_state = RUNNING; }
		return;
	}
}
static void cmd_info_r() {
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
static void cmd_x(uint32_t para,uint32_t addr)
{
	int i;
	for (i=0;i<para;i++) {
		printf("%8x:	",addr);
		int j;
		for (j=0;j<4;j++) {
			printf("%02x ", swaddr_read(addr+j,1));
		}
		printf("\n");
		addr+=4;
	}
}
static void cmd_info_b() {
	info_b();
}
static void cmd_b(int addr) {
	if (nemu_state==END){
		printf("No program running!\n");
		return ;
	}
	int temp;
	temp=swaddr_read(addr,1);
	BP *new=new_bp();
	new->origin=temp;
	new->addr=addr;
	printf("Breakpoint set at 0x%x.\n",addr);
	swaddr_write(addr,1,0xcc);
}
static void cmd_d(int para) {
	delete_bp(para);
}
static void cmd_p(char *p) {
	bool success;
	expr(p,&success);
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
			cmd_si(para);
		}														       
		else if(strcmp(p, "info") == 0) {							
			p = strtok(NULL," ");
			if (p == NULL)
				printf("Invalid parameter!\n");
			else {
				if (strcmp(p, "r") == 0) {
					cmd_info_r();	
				}
				else {
					if (strcmp(p, "b") == 0) {
						cmd_info_b();
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
				p = strtok(NULL," ");
				if (p == NULL) 
					printf("Invalid parameter!\n");
				else { 
					sscanf(p,"%x",&addr);
					cmd_x(para,addr);
				}
			}
		}
		else if(strcmp(p, "b") == 0) {
			p = strtok(NULL," *");
			if (p == NULL)
				printf("Invalid parameter!\n");
			else {
				sscanf(p,"%x",&addr);
				cmd_b(addr);
			}
		}
		else if(strcmp(p, "d") == 0) {
			p = strtok(NULL," ");
			if (p == NULL)
				printf("Invalid parameter!\n");
			else {
				sscanf(p,"%d",&para);
				cmd_d(para);
			}
		}
		else if(strcmp(p, "p") == 0) {
			p = strtok(NULL," ");
			if (p == NULL)
				printf("Invalid parameter!\n");
			else 
				cmd_p(p);
		}
		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
	}
}
