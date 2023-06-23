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
#include "CPU.h"
#include "Memoria.h"
#include "Scheduler.h"

struct Pcb exekuzioan;

int IlaraAukeraketa() {

  int random = (rand() % (10 - 1 + 1)) + 1; 

  return random;

}

void* MemoriaStackGarbitu(int ind) {

    for (int i = 0; i < maxVirtualSpace; i++)
    {
        MemoriaBirtuala[ind].code_v[i].v_page = '0';
        MemoriaBirtuala[ind].data_v[i].v_page = '0';
    }

    MemoriaBirtuala[ind].inuse = 0;
    
}


void* Dispatch() {

    int aukeraketa, unekoDenb;
    unsigned long ezabpid;
    int stackind = -1;
    aukeraketa = IlaraAukeraketa();

    if (aukeraketa <= 7) {

        exekuzioan = ezabatuProPrio();

        unekoDenb = exekuzioan.egoera - CPU_ahalmena;

        if (unekoDenb > 0) {

            exekuzioan.egoera = unekoDenb;
            gehituProPrio(exekuzioan);
            printf("%lu prozesua lehentasun altuko ilarara itzuli da, denbora hau geratzen zaiolarik: %d \n", exekuzioan.pid, exekuzioan.egoera);

        } else {

            ezabpid = exekuzioan.pid;
            stackind = exekuzioan.mm.code;
            //MemoriaStackGarbitu(stackind);

        }

    } else {

        exekuzioan = ezabatuPro();

        unekoDenb = exekuzioan.egoera - CPU_ahalmena;

        if (unekoDenb > 0) {

            exekuzioan.egoera = unekoDenb;
            gehituPro(exekuzioan);
            printf("%lu prozesua lehentasun baxuko ilarara itzuli da, denbora hau geratzen zaiolarik: %d \n", exekuzioan.pid, exekuzioan.egoera);

        } else {

            ezabpid = exekuzioan.pid;
            stackind = exekuzioan.mm.code;
            //MemoriaStackGarbitu(stackind);
            //printf("%lu prozesuaren exekuzioa bukatu da, memoria stack hau garbituz: %d, code0_v_page: %c \n", ezabpid, stackind, MemoriaBirtuala[stackind].code_v[0].v_page);
            //printf("%lu prozesuaren exekuzioa bukatu da \n", exekuzioan.pid);

        }


    }

    if (stackind != -1) {
        MemoriaStackGarbitu(stackind);
        printf("%lu prozesuaren exekuzioa bukatu da, memoria stack hau garbituz: %d \n", ezabpid, stackind);
    }

}