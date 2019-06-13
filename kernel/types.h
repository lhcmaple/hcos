#ifndef _TYPES_H
#define _TYPES_H

#include "etc.h"

#define NULL ((void *)0)

typedef void (*TaskFUNC)(void *);
typedef int sem_t;
typedef unsigned int time_t;

struct TaskTCB{
	char *stack_top;//进程堆栈保存处
	struct TaskTCB *next;//下一任务
	char stack[STACK_SIZE];//进程堆栈
	int pid;//进程ID
	int priority;
	TaskFUNC task_func;//初始化任务函数
	void *pvalue;//初始化参数
};

#endif
