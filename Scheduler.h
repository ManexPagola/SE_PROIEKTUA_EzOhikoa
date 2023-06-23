#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>

#include "ProcessQueue.h"

extern struct Pcb exekuzioan;

int IlaraAukeraketa();
void* MemoriaStackGarbitu(int ind);
void* Dispatch();


#endif