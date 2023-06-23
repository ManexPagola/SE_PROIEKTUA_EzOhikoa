#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

//#include "CPU.h"

#define TH_MAX 10
#define CORE_MAX 10
#define CPU_MAX 10
#define TLB_MAX 256

struct TLB_sarrera
{
	int index;
	int full;
	unsigned char v_page;
	unsigned char f_page;
};

struct TLB
{
	struct TLB_sarrera tlb_array[TLB_MAX];
};

struct MMU {
    struct TLB tlb;
};

struct Hw_hari {
    int tid;
	unsigned int ptbr;
	unsigned int pc;
	unsigned int ir;
    struct MMU mmu;
};


struct Hw_hari Th_array[CPU_MAX][CORE_MAX][TH_MAX];
//pthread_t hari;

int CPU_ahalmena;

void CPU_ahalKalk(int p) {

    int var = p / 20;

    CPU_ahalmena = var + 1;

    printf("CPU Ahalmena: %d \n", CPU_ahalmena);

}

struct TLB tlb_hasieratu(struct TLB *tlbpar) {
	int tlb_i;
	//struct TLB_sarrera array[TLB_MAX];
	for (tlb_i = 0; tlb_i < TLB_MAX; tlb_i++)
	{
        tlbpar->tlb_array[tlb_i].index = tlb_i;
        tlbpar->tlb_array[tlb_i].full = 0;
	}
	//tlbpar->tlb_array = tlb_array;
    return *tlbpar;
}

struct MMU mmu_hasieratu(struct MMU *mmupar) {
	struct TLB tlbald;
	struct TLB *tlb_pt = &tlbald;
	tlbald = tlb_hasieratu(tlb_pt);
	mmupar->tlb = tlbald;
	return *mmupar; 

}

void Hw_hari_hasieratu(struct Hw_hari *hari, int id) {
	hari->tid = id;
	hari->pc = 0;
	hari->ir = 0;
	hari->ptbr = 0;
	struct MMU mmup;
	struct MMU *mmu_pt = &mmup;
	mmup = mmu_hasieratu(mmu_pt);
	hari->mmu = mmup;
}

int HiruDtik1Dra(int x, int y, int z) {
	return (x * CPU_MAX * CORE_MAX) + (y * CPU_MAX) + z;
}

void CPU_Hasieratu(int CPU_kop, int core_kop, int hari_kop)
{
int i, j, k;

	for (i=0; i <= CPU_kop; i++) {

		for (j=0; j <= core_kop; j++) {

			for (k=0; k <= hari_kop; k++) {
			
				struct Hw_hari hari;
                struct Hw_hari *hari_pt = &hari;
				int idth = HiruDtik1Dra(i, j, k);
				Hw_hari_hasieratu(hari_pt, idth);
				Th_array[i][j][k] = hari; 
			}
		}
	}	


    int balioa = CPU_kop * core_kop * hari_kop;

    CPU_ahalKalk(balioa);

    /*printf("tlb_index_100_100: %d \n", Th_array[1][0][0].mmu.tlb.tlb_array[100].index);
    printf("tlb_index_100_200: %d \n", Th_array[1][0][0].mmu.tlb.tlb_array[200].index);
    printf("tlb_index_200_100: %d \n", Th_array[2][0][0].mmu.tlb.tlb_array[100].index);
    printf("tlb_index_200_200: %d \n", Th_array[2][0][0].mmu.tlb.tlb_array[200].index);*/

	int a,b,c;
	for (a=0; a <= CPU_kop; a++) {

                for (b=0; b <= core_kop; b++) {

                        for (c=0; c <= hari_kop; c++) {

                                printf("%d %d %d = %d\n", a,b,c,Th_array[a][b][c].tid); 
                        }
                }
    } 
}

