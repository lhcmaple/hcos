#include "etc.h"
#include "types.h"
#include "../cpu/cpu.h"

struct TaskTCB *tasks[NPRIORITY];
struct TaskTCB *current;
struct TaskTCB idlepcb;
int taskpid;

void idletask(void *);

void initsystem(void)
{
	tasks[0]=NULL;
	taskpid=0;
}

int addtasktolist(struct TaskTCB *taskp,int priority,TaskFUNC ptask_func,void *pvalue)
{
	//R4-R11,R0-R3,R12,R14,R15,xPSR
	if(priority<0||priority>=NPRIORITY)
		return -1;
	taskp->stack_top=taskp->stack+STACK_SIZE;
	*((int **)(taskp->stack_top-0x8))=(int *)ptask_func;
	*((int *)(taskp->stack_top-0x4))=0x01000000;//xPSR的初始值
	*((void **)(taskp->stack_top-0x20))=pvalue;//传递参数
	taskp->stack_top-=0x40;
	if(tasks[priority])
	{
		taskp->next=tasks[priority]->next;
		tasks[priority]->next=taskp;
	}
	else
	{
		taskp->next=taskp;
		tasks[priority]=taskp;
	}
	taskp->pid=(taskpid++);
	taskp->priority=priority;
	taskp->task_func=ptask_func;
	taskp->pvalue=pvalue;
	return 0;
}

void startsystem(void)
{
	int i;
	addtasktolist(&idlepcb,NPRIORITY-1,idletask,NULL);
	for(i=0;i<NPRIORITY;++i)
		if(tasks[i])
		{
			current=tasks[0];
			break;
		}
	if(current==NULL)
		addtasktolist(&idlepcb,NPRIORITY-1,idletask,NULL);
	__startsystem();
}

void idletask(void *pvalue)
{
	while(1)
	{
		;//空闲任务
	}
}

void schedule(void)
{
	__schedule();
}
