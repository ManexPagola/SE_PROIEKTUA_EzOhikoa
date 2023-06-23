#ifndef PROCESSGENERATOR_H
#define PROCESSGENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>

#include "ProcessQueue.h"


extern struct MemoryManagement memm;
extern struct MemoryManagement *memm_pt;
extern struct Pcb prozesua;
extern pthread_t proGen;

void* ProzesuHuts();

struct MemoryManagement MM_Hasieratu(struct MemoryManagement *mm);

int ExekDenboraLortu();

int MemoriaStackEsleitu();

void* ProzesuSortzaile();




#endif
