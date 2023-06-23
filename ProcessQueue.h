#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H
#include <stdbool.h>

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


extern struct Pcb ProcessQueue[PRO_MAX];
extern struct Pcb ProcessQueuePrio[PRO_MAX_PRIO];

struct Pcb buruaErakutsi();
struct Pcb buruaErakutsiPrio();

bool hutsaDa();
bool hutsaDaPrio();

bool beteaDago();
bool beteaDagoPrio();

int tamaina();
int tamainaPrio();

void gehituPro(struct Pcb);
void gehituProPrio(struct Pcb);

struct Pcb ezabatuPro();
struct Pcb ezabatuProPrio();

#endif
