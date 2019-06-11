#include "../kernel/sched.h"
#include "../kernel/types.h"
#include "../kernel/etc.h"

extern struct TaskTCB;

struct TaskTCB task1;
struct TaskTCB task2;
struct TaskTCB task3;
struct TaskTCB task4;

int value1;
int value2;
int value3;
int value4;

void task_func1(void *);
void task_func2(void *);
void initsystem(void);
void addtasktolist(struct TaskTCB *,TaskFUNC,void *);
void startsystem(void);

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
