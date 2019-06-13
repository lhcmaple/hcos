#include "../kernel/etc.h"

__asm void __startsystem(void)
{
	IMPORT current
	LDR R0,=current
	LDR R0,[R0]
	LDR R1,[R0];R1此时等于current->stack_top

	MOV R0,#0x02
	MSR CONTROL,R0;切换堆栈
	MOV SP,R1
	ADD SP,#0x40
	LDR R0,[R1,#0x20]
	LDR LR,[R1,#0x38]

;设置调度时钟
	LDR R3,=0xE000E010
	LDR R4,=0xE000E014
	LDR R7,[R3]
	ORR R7,#0x7
	STR R7,[R3]
	MOV R7,#11999;1ms
	STR R7,[R4]

	BX LR
}

__asm void __schedule(void)
{
NVIC_ICSR EQU 0xE000ED04
	IMPORT systime
	LDR R0,=NVIC_ICSR
	MOV R1,#0x10000000
	STR R1,[R0]
	BX LR
	NOP
}
