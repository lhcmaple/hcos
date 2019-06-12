#ifndef _SCHED_H
#define _SCHED_H

#include "types.h"

void initsystem(void);
void addtasktolist(struct TaskTCB *,TaskFUNC,void *);
void startsystem(void);

#endif
