#ifndef _SEM_H
#define _SEM_H

#include "types.h"

int seminit(sem_t *,int);
int semdown(sem_t *);
int semup(sem_t *);

#endif
