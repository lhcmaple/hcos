#include "../kernel/sched.h"
#include "../kernel/types.h"
#include "../kernel/etc.h"
#include "../kernel/sem.h"

struct TaskTCB task1;
struct TaskTCB task2;
struct TaskTCB task3;
struct TaskTCB task4;

int value1;
int value2;
int value3;
int value4;
sem_t sem1;

void task_func1(void *);
void task_func2(void *);

int main()
{
	initsystem();
	seminit(&sem1,1);
	addtasktolist(&task1,0,&task_func1,&value1);
	addtasktolist(&task2,1,&task_func2,&value2);
	addtasktolist(&task3,0,&task_func1,&value1);
	addtasktolist(&task4,1,&task_func1,&value1);
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
		schedule();
	}
}
