#include "etc.h"
#include "types.h"
#include "../cpu/cpu.h"

struct TaskTCB *tasks[1];
struct TaskTCB *current;
struct TaskTCB idlepcb;
int taskpid;

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

void idletask(void *pvalue)
{
	while(1)
	{
		;//空闲任务
	}
}
