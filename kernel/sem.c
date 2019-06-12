#include "types.h"

int seminit(sem_t *sem,int value)
{
	if(value<0)
		return -1;
	*sem=value;
	return 0;
}

__asm int semdown(sem_t *sem)
{
SEMDOWNTRY
	LDREX R1,[R0]
	CMP R1,#0x0
	BEQ SEMDOWNTRY
	SUB R1,#0x1
	MOV R2,#0x0
	STREX R2,R1,[R0]
	CMP R2,#0x1
	BEQ SEMDOWNTRY
	BX LR
}

__asm int semup(sem_t *sem)
{
SEMUPTRY
	LDREX R1,[R0]
	ADD R1,#0x1
	MOV R2,#0x0
	STREX R2,R1,[R0]
	CMP R2,#0x1
	BEQ SEMUPTRY
	BX LR
}
