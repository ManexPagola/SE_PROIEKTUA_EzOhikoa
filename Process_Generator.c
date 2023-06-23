#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h>


#include "ProcessQueue.h"
#include "Process_Generator.h"
#include "Memoria.h"

//int tick=0;
int j=0;
struct MemoryManagement memm;
struct MemoryManagement *memm_pt =  &memm;
struct Pcb prozesua;
pthread_t proGen;
//pthread_mutex_t mutexProzesu;
//pthread_mutex_t mutexProzesu2;

void* ProzesuHuts() { 
	sleep(0);
}

struct MemoryManagement MM_Hasieratu(struct MemoryManagement *mm) {
  mm->code = 0;
  mm->data = 5000;
  mm->pgb = 0;

  return *mm;
}


int ExekDenboraLortu() {

  int random = (rand() % (1000 - 100 + 1)) + 100; 

  return random;

}

int MemoriaStackEsleitu() {
  int esleipena = -1;
  int i=0;
  int aurkitua = 0;

  while (aurkitua==0 && i < maxVirtualStacks) {

    if (MemoriaBirtuala[i].inuse == 0) {

      esleipena = i;
      aurkitua = 1;
      
    }

    i++;

  }

  return esleipena;

}

void* ProzesuSortzaile() {

  int mem_toki;
  int exekDenb;
  int prio=0;
    if (pthread_create(&proGen, NULL, &ProzesuHuts, NULL) != 0) { 
		      fprintf(stderr, "Errorea prozesu sortzailearen haria sortzen \n");
          exit(EXIT_FAILURE);
    }
    prozesua.pid = proGen;
    exekDenb = ExekDenboraLortu();
    prozesua.exekdenb = exekDenb;
    prozesua.egoera = exekDenb;

    memm = MM_Hasieratu(memm_pt);
    prozesua.mm = memm;

    mem_toki = MemoriaStackEsleitu();

    if (mem_toki != -1) {

      prozesua.mm.code = mem_toki;
      prozesua.mm.data = mem_toki;
      MemoriaBirtuala[mem_toki].inuse = 1;

    }

 
    if (exekDenb <= 400) {
        prozesua.prio = 1;
        gehituProPrio(prozesua);
    } else {
        prozesua.prio = 0;
        gehituPro(prozesua);
    }

}

