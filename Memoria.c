#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h>

#define maxNode 20
#define maxVirtualSpace 10
#define maxVirtualStacks 1000
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


struct MemFisikoa MemFisGlobal;
struct StackBirtuala MemoriaBirtuala[maxVirtualStacks];

void* MemBirtuala_Hasieratu(struct StackBirtuala *membirtpar) {

    for (int i=0; i<maxVirtualStacks; i++) {
        for (int j=0; j<maxVirtualSpace; j++) {

            membirtpar[i].code_v[j].offset = j;
            membirtpar[i].code_v[j].v_page = '0';

            membirtpar[i].data_v[j].offset = j;
            membirtpar[i].data_v[j].v_page = '0';

        }
        membirtpar->inuse = 0;
    }

}

struct CodeMem CodeMem_Hasieratu(struct CodeMem *codepar) {
    codepar->code_helb = 0;

    struct OrriFisikoa orricode;

    for (int i = 0; i < maxCodeFrame; i++)
    {
        orricode.id = i;
        for(int j=0; j < maxNode; j++) orricode.node_array[j] = '0';

        codepar->codePage_array[i] = orricode;
    }

    return *codepar;

}

struct DataMem DataMem_Hasieratu(struct DataMem *datapar) {
    datapar->data_helb = maxDataFrame;

    struct OrriFisikoa orridata;

    for (int i = 0; i < maxDataFrame; i++)
    {
        orridata.id = maxDataFrame + i;
        for(int j=0; j < maxNode; j++) orridata.node_array[j] = '0';

        datapar->dataPage_array[i] = orridata;
    }

    return *datapar;
    
}

struct PageTable PTable_Hasieratu(struct PageTable *ptabpar) {
    ptabpar->pt_helb = 0;

    struct PT_errenkada pterr;

    for (int i = 0; i < maxFrame; i++) {

        
        pterr.f_pageid = 0;
        pterr.v_page = '0';

        ptabpar->PT_array[i] = pterr;

    }

    return *ptabpar;
    
}

void* MemoriaHasieratu() {
    struct MemFisikoa *memfis_pt = &MemFisGlobal;
    struct StackBirtuala *membir_pt = &MemoriaBirtuala;

    MemBirtuala_Hasieratu(membir_pt);

    struct CodeMem codem;
    struct CodeMem *codem_pt = &codem;
    struct DataMem datam; 
    struct CodeMem *datam_pt = &datam;
    struct PageTable ptab;
    struct PageTable *ptab_pt = &ptab;

    codem = CodeMem_Hasieratu(codem_pt);
    datam = DataMem_Hasieratu(datam_pt);
    ptab = PTable_Hasieratu(ptab_pt);

    memfis_pt->codemem = codem;
    memfis_pt->datamem = datam;
    memfis_pt->ptable = ptab;

    /*printf("fisiko code_helb: %d 1000 code_pageid: %d code_pagenode: %s \n", MemFisGlobal.codemem.code_helb, MemFisGlobal.codemem.codePage_array[1000].id, MemFisGlobal.codemem.codePage_array[1000].node_array);
    printf("fisiko data_helb: %d 1000 data_pageid: %d data_pagenode: %s \n", MemFisGlobal.datamem.data_helb, MemFisGlobal.datamem.dataPage_array[1000].id, MemFisGlobal.datamem.dataPage_array[1000].node_array);
    printf("fisiko pt_helb: %d 1000 pt_vpage: %c pt_fis_id: %d pt_fis_pagenode: %s \n", MemFisGlobal.ptable.pt_helb, MemFisGlobal.ptable.PT_array[1000].v_page, MemFisGlobal.ptable.PT_array[1000].f_page.id, MemFisGlobal.ptable.PT_array[1000].f_page.node_array);
    */

    //printf("birtualstack5 code_v5 offset: %d v_page: %c \n", MemoriaBirtuala[5].code_v[5].offset, MemoriaBirtuala[5].code_v[5].v_page);
    //printf("birtualstack5 data_v5 offset: %d v_page: %c \n", MemoriaBirtuala[5].data_v[5].offset, MemoriaBirtuala[5].data_v[5].v_page);

}

void* AginduakKargatu() {

    FILE *fptr;

    fptr = fopen("aginduak.txt", "r");

    char aginduak[100];

    if(fptr != NULL) {

        int j=0;

        while(fgets(aginduak, 100, fptr)) {
            char* zati = strtok(aginduak, " ");
            int i=0;
            char* code;
            char* data;
            while (zati != NULL) {
                if (i==0) {
                    code = zati;
                } else if (i==1) {
                    data = zati;
                }
                i++;
                zati = strtok(NULL, " ");
            }

            //int codelen = strlen(code);
            //printf("j = %d, codelen: %d\n", j, codelen);
            //int datalen = strlen(data);
            //printf("j = %d, datalen: %d\n", j, datalen);

            strcpy(MemFisGlobal.codemem.codePage_array[j].node_array, code);
            strcpy(MemFisGlobal.datamem.dataPage_array[j].node_array, data);


            MemFisGlobal.ptable.PT_array[j].f_pageid = j;
            MemFisGlobal.ptable.PT_array[maxDataFrame + j].f_pageid = maxDataFrame + j;

            
            

            //printf("code%d: %s\n", j, MemFisGlobal.codemem.codePage_array[j].node_array);
            //printf("data%d: %s\n", j, MemFisGlobal.datamem.dataPage_array[j].node_array);

            j++;
            //printf("code: %s\n", code);
            //printf("data: %s\n", data);
            

        }


    } else {
        printf("Ezin izan da aginduen fitxategia ireki \n");
    }

    fclose(fptr); 

}