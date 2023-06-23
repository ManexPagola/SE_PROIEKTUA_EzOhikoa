#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>


#include "Process_Generator.h"
#include "Scheduler.h"

pthread_mutex_t mutexTick;
pthread_cond_t condTick;
pthread_cond_t condTick2;
sem_t sem1;
int tick=0;
int tick2=0;
int count=0;
int tenp_kop=2;

void* Erlojua() { 	
	while (1) {
		pthread_mutex_lock(&mutexTick);
		while (count < tenp_kop) {
			pthread_cond_wait(&condTick, &mutexTick);
		}
	count=0;
	pthread_cond_broadcast(&condTick2);
	pthread_mutex_unlock(&mutexTick);
	}
}

void* Tenporizadorea_pro(int f) { 
	pthread_mutex_lock(&mutexTick);
	//sem_init(&sem1, 0, 1);
	//printf("Balioa: %d\n", f);
	//printf("Tenporizadorea iritsi da\n");
	while (1) {
		count++;
		tick++;
		//printf("Kontagailua: %d\n", tick);
		if (tick == f) {
			sem_wait(&sem1);
			ProzesuSortzaile();
			//printf("Prozesuen tenporizadoreak seinalea bidali du tick honetan: %d\n",tick);
			tick = 0;
			sem_post(&sem1);
		}
		pthread_cond_signal(&condTick);
		pthread_cond_wait(&condTick2, &mutexTick);
	}
	//sem_destroy(&sem1);
}

void* Tenporizadorea_sch(int f) { 
	pthread_mutex_lock(&mutexTick);
	//printf("Balioa: %d\n", f);
	//printf("Tenporizadorea iritsi da\n");
	while (1) {
		count++;
		tick2++;
		//printf("Kontagailua: %d\n", tick);
		if (tick2 == f) {
			sem_wait(&sem1);
			Dispatch();
			//printf("Schedulerraren tenporizadoreak seinalea bidali du tick honetan: %d\n",tick2);
			tick2 = 0;
			sem_post(&sem1);
		}
		pthread_cond_signal(&condTick);
		pthread_cond_wait(&condTick2, &mutexTick);
	}
}

