#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define TH_MAX 10
#define CORE_MAX 10
#define CPU_MAX 10
#define TLB_MAX 256

extern int CPU_ahalmena;

extern struct TLB_sarrera
{
	int index;
	int full;
	unsigned char v_page;
	unsigned char f_page;
};


extern struct  TLB
{
	struct TLB_sarrera tlb_array[TLB_MAX];
};


extern struct MMU {
    struct TLB tlb;
}; 


extern struct Hw_hari {
    int tid;
    unsigned int ptbr;
    unsigned int pc;
	unsigned int ir;
    struct MMU mmu;
};

extern struct Hw_hari Th_array[CPU_MAX][CORE_MAX][TH_MAX];

int HiruDtik1Dra(int x, int y, int z);
void Hw_hari_hasieratu(struct Hw_hari hari, int id);
struct MMU mmu_hasieratu(struct MMU *mmupar);
struct TLB tlb_hasieratu(struct TLB *tlbpar);
void CPU_Hasieratu(int CPU_kop, int core_kop, int hari_kop);
void CPU_ahalKalk(int p);

#endif