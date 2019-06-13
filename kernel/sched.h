#ifndef _SCHED_H
#define _SCHED_H

#include "types.h"

void initsystem(void);
int addtasktolist(struct TaskTCB *,int,TaskFUNC,void *);
void startsystem(void);
void schedule(void);

#endif
