#include "etc.h"
#include "types.h"

struct TaskTCB{
	char *stack_top;//进程堆栈保存处
	struct TaskTCB *next;//下一任务
	char stack[STACK_SIZE];//进程堆栈
	int pid;//进程ID
	TaskFUNC task_func;//初始化任务函数
	void *pvalue;//初始化参数
};

struct TaskTCB *tasks[1];
struct TaskTCB *current;
struct TaskTCB idlepcb;
int taskpid;

void __asm __startsystem(void);
void idletask(void *);

void initsystem(void)
{
	tasks[0]=NULL;
	taskpid=0;
}

void addtasktolist(struct TaskTCB *taskp,TaskFUNC ptask_func,void *pvalue)
{
	//R4-R11,R0-R3,R12,R14,R15,xPSR
	taskp->stack_top=taskp->stack+STACK_SIZE;
	*((int **)(taskp->stack_top-0x8))=(int *)ptask_func;
	*((int *)(taskp->stack_top-0x4))=0x01000000;//xPSR的初始值
	*((void **)(taskp->stack_top-0x20))=pvalue;//传递参数
	taskp->stack_top-=0x40;
	if(tasks[0])
	{
		taskp->next=tasks[0]->next;
		tasks[0]->next=taskp;
	}
	else
	{
		taskp->next=taskp;
		tasks[0]=taskp;
	}
	taskp->pid=(taskpid++);
	taskp->task_func=ptask_func;
	taskp->pvalue=pvalue;
}

void startsystem(void)
{
	current=tasks[0];
	if(current==NULL)
		addtasktolist(&idlepcb,idletask,NULL);
	__startsystem();
}

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
	MOV R7,#0x80
	STR R7,[R4]

	BX LR
}

void idletask(void *pvalue)
{
	while(1)
	{
		;//空闲任务
	}
}
