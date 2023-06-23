#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h>

#define maxNode 4
#define maxVirtualSpace 10
#define maxVirtualStacks 1000
//#define maxVirtualPage 10000
#define maxCodeFrame 16384
#define maxDataFrame 16384
#define maxFrame 32768

typedef struct OrriFisikoa {
    int id;
    unsigned char node_array[maxNode];
} OrriFisikoa;

typedef struct PT_errenkada {
    unsigned char v_page;
    unsigned int f_pageid;
    //struct OrriFisikoa f_page;
} PT_errenkada;


typedef struct CodeMem {
    unsigned int code_helb;
    struct OrriFisikoa codePage_array[maxCodeFrame];
} CodeMem;

typedef struct DataMem {
    unsigned int data_helb;
    struct OrriFisikoa dataPage_array[maxDataFrame];
} DataMem;

typedef struct PageTable {
    unsigned int pt_helb;
    struct  PT_errenkada PT_array[maxFrame];
} PageTable;

typedef struct OrriBirtuala {
    unsigned char v_page;
    unsigned int offset;
} OrriBirtuala;


typedef struct MemFisikoa {
    struct CodeMem codemem;
    struct DataMem datamem;
    struct PageTable ptable;
} MemFisikoa;

typedef struct StackBirtuala {
    struct OrriBirtuala code_v[maxVirtualSpace];
    struct OrriBirtuala data_v[maxVirtualSpace];
    unsigned int inuse;
} StackBirtuala;

extern struct MemFisikoa MemFisGlobal;
extern struct StackBirtuala MemoriaBirtuala[maxVirtualStacks];
//extern struct OrriBirtuala MemoriaBirtuala[maxVirtualPage];

//void* MemBirtuala_Hasieratu(struct OrriBirtuala *membirtpar);
void* MemBirtuala_Hasieratu(struct StackBirtuala *membirtpar);
struct CodeMem CodeMem_Hasieratu(struct CodeMem *codepar);
struct DataMem DataMem_Hasieratu(struct DataMem *datapar);
struct PageTable PTable_Hasieratu(struct PageTable *ptabpar);
void* MemoriaHasieratu();
void* AginduakKargatu();