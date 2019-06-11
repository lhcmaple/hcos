#include "types.h"

extern struct TaskTCB;

void initsystem(void);
void addtasktolist(struct TaskTCB *,void (*)(void *),void *);
void startsystem(void);
