#ifndef ERLOJUA_H
#define ERLOJUA_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>


extern pthread_mutex_t mutexTick;
extern pthread_cond_t condTick;
extern pthread_cond_t condTick2;

extern sem_t sem1;


void* Erlojua();

void* Tenporizadorea_pro(int f);

void* Tenporizadorea_sch(int f);

#endif