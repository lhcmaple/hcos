#define STACK_SIZE 0x400
#define NULL ((void *)0)

struct task_pcb{
	char *task_top;//进程堆栈保存处
	struct task_pcb *next;
	char stack[STACK_SIZE];//进程堆栈
	int pid;
	void (*task_func)(void *);//初始化任务函数
	void *pvalue;//初始化参数
};

struct task_pcb task_list;
int taskpid;
struct task_pcb *current;
struct task_pcb task1;
struct task_pcb task2;
struct task_pcb task3;
struct task_pcb task4;
int value1;
int value2;
int value3;
int value4;

void task_func1(void *);
void task_func2(void *);
void initsystem(void);
void addtasktolist(struct task_pcb *,void (*)(void *),void *);
void startsystem(void);
__asm void __startsystem(void);

int main()
{
	initsystem();
	addtasktolist(&task1,&task_func1,&value1);
	addtasktolist(&task2,&task_func2,&value2);
	addtasktolist(&task3,&task_func1,&value3);
	addtasktolist(&task4,&task_func1,&value4);
	startsystem();
	return 0;
}

void initsystem(void)
{
	task_list.next=NULL;
	taskpid=0;
}

void addtasktolist(struct task_pcb *taskp,void (*ptask_func)(void *),void *pvalue)
{
	struct task_pcb *tp;
	tp=(&task_list)->next;
	if(tp)
	{
		taskp->next=tp->next;
		tp->next=taskp;
	}
	else
	{
		(&task_list)->next=taskp;
		taskp->next=taskp;
	}
	taskp->pvalue=pvalue;
	taskp->pid=(++taskpid);
	taskp->task_func=ptask_func;
	taskp->task_top=taskp->stack+STACK_SIZE;
	*((int **)(taskp->task_top-8))=(int *)ptask_func;
	*((int *)(taskp->task_top-4))=0x01000000;
	taskp->task_top-=0x40;
	*((void **)(taskp->task_top+0x20))=taskp->pvalue;//传递参数
	//R4-R11,R0-R3,R12,R14,R15,xPSR
}

void startsystem(void)
{
	current=(&task_list)->next;
	__startsystem();
}

void task_func1(void *pvalue)
{
	while(1)
	{
		*((int *)pvalue)+=1;
	}
}

void task_func2(void *pvalue)
{
	while(1)
	{
		*((int *)pvalue)+=1;
	}
}

__asm void __startsystem(void)
{
	IMPORT current
	LDR R0,=current
	LDR R0,[R0]
	LDR R1,[R0];R1此时等于current->task_top

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
