#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>

#define PRO_MAX 100

#define PRO_MAX_PRIO 50

struct MemoryManagement {
   int pgb;
   int code;
   int data;
};

typedef struct Pcb {
    pthread_t pid;
    int prio;
    int egoera;
    int exekdenb;
    struct MemoryManagement mm; 
} Pcb;

struct Pcb ProcessQueue[PRO_MAX];
struct Pcb ProcessQueuePrio[PRO_MAX_PRIO];

int burua = 0; 
int buztana = -1; 
int elemkop = 0;  

int buruaPrio = 0; 
int buztanaPrio = -1; 
int elemkopPrio = 0;  

struct Pcb buruaErakutsi() {
   return ProcessQueue[burua];
}

struct Pcb buruaErakutsiPrio() {
   return ProcessQueuePrio[buruaPrio];
}


bool hutsaDa() {
   return elemkop == 0;
}

bool hutsaDaPrio() {
   return elemkopPrio == 0;
}

bool beteaDago() {
   return elemkop == PRO_MAX;
}

bool beteaDagoPrio() {
   return elemkopPrio == PRO_MAX_PRIO;
}

int tamaina() {
   return elemkop;
}  

int tamainaPrio() {
   return elemkopPrio;
}  

void gehituPro(struct Pcb prozesu) {

   if(!beteaDago()) {
	
      if(buztana == PRO_MAX-1) {
         buztana = -1;            
      }       

      ProcessQueue[++buztana] = prozesu;
      elemkop++;

      printf("Lehentasun gutxiko ilaran gehitu da: %lu, memoria birtual zati hau esleiturik: %d\n", ProcessQueue[buztana].pid, ProcessQueue[buztana].mm.code);
   }
}

void gehituProPrio(struct Pcb prozesu) {

   if(!beteaDagoPrio()) {
	
      if(buztanaPrio == PRO_MAX_PRIO-1) {
         buztanaPrio = -1;            
      }       

      ProcessQueuePrio[++buztanaPrio] = prozesu;
      elemkopPrio++;

      printf("Lehentasun handiko ilaran gehitu da: %lu, memoria birtual zati hau esleiturik: %d\n", ProcessQueuePrio[buztanaPrio].pid, ProcessQueuePrio[buztanaPrio].mm.code);
   }
}

struct Pcb ezabatuPro() {
   struct Pcb prozesu = ProcessQueue[burua++];
	
   if(burua == PRO_MAX) {
      burua = 0;
   }
	
   elemkop--;
   return prozesu;  
}

struct Pcb ezabatuProPrio() {
   struct Pcb prozesu = ProcessQueuePrio[buruaPrio++];
	
   if(buruaPrio == PRO_MAX_PRIO) {
      buruaPrio = 0;
   }
	
   elemkopPrio--;
   return prozesu;  
}