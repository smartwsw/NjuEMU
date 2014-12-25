#ifndef __CPU_REG_H__
#define __CPU_REG_H__

#include "common.h"

/* TODO: Re-organize the 'CPU_state' structure to match
 * the GPR encoding scheme in i386 instruction format.
 * For example, if we access reg_w(R_BX) we will get the 'bx' register;
 * if we access reg_b(R_CH), we will get the 'ch' register.
 * Hint: Use 'union'.
 * For more details about the GPR encoding scheme, see i386 manual.
 */
typedef struct SegmentDescriptor {
	uint32_t limit_15_0          : 16; 
	uint32_t base_15_0           : 16; 
	uint32_t base_23_16          : 8;
	uint32_t type                : 4;
	uint32_t segment_type        : 1;
	uint32_t privilege_level     : 2;
	uint32_t present             : 1;
	uint32_t limit_19_16         : 4;
	uint32_t soft_use            : 1;
	uint32_t operation_size      : 1;
	uint32_t pad0                : 1;
	uint32_t granularity         : 1;
	uint32_t base_31_24          : 8;
} SegDesc;

typedef union {
	union{
		uint32_t _32;
		uint16_t _16;
		uint8_t _8[2];
	} gpr[8];

	/* Do NOT change the order of the GPRs' definitions. 
	 * They match the register encoding scheme used in i386 instruction format.
	 * See i386 manual for more details.
	 */

	struct {
		uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
		swaddr_t eip;
		union {
			uint32_t EFLAGS;
			struct {uint32_t CF:1,NAN1:1,PF:1,NAN2:1,AF:1,NAN3:1,ZF:1,SF:1,TF:1,IF:1,DF:1,OF:1,IOPL:2,NT:1,NAN4:1,RF:1,VM:1,NAN5:15;};
		};
		struct {
			uint32_t base;
			uint16_t limit;
		} GDTR;
		union {
			uint32_t CR0;
			struct {
				uint32_t PE:1, MP:1, EM:1, TS:1, ET:1, RESERVED:26, PG:1;
			};
		};
		struct {
			union {
				struct {
					uint16_t RPL	:2;
					uint16_t TI		:1;
					uint16_t INDEX	:13;
				};
				uint16_t val;
			};
			union {
				SegDesc hide;
				int64_t hide_val;
			};
		} CS, SS, DS, ES;
	};

} CPU_state;

extern CPU_state cpu;

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

#define reg_l(index) (cpu.gpr[index]._32)
#define reg_w(index) (cpu.gpr[index]._16)
#define reg_b(index) (cpu.gpr[index & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

#endif
