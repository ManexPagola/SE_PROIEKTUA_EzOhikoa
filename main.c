#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <semaphore.h>
#include <time.h>


#include "Process_Generator.h"
#include "ProcessQueue.h"
#include "Erlojua.h"
#include "CPU.h"
#include "Scheduler.h"
#include "Memoria.h"

int CPU_kop, core_kop, hari_kop, maiz_Pro, maiz_Sch;

int main(int argc, char *argv[])
{

    srand(time(NULL));

    printf("\n");

    printf("---------------KONFIGURAZIOA HASTEN----------------\n");

    printf("\n");

    printf("Sartu makinaren CPU kopurua: \n");
    scanf("%d", &CPU_kop);

    if (CPU_kop > CPU_MAX)
    {
        CPU_kop = CPU_MAX;
        printf("CPU gehiegi, makinaren maximoa aukeratu da: %d \n", CPU_MAX);
    }
    else if (CPU_kop < 1)
    {
        CPU_kop = 1;
        printf("CPU gutxiegi, makinaren minimoa aukeratu da: 1 \n");
    }

    printf("Sartu makinaren core kopurua: \n");
    scanf("%d", &core_kop);

    if (core_kop > CORE_MAX)
    {
        core_kop = CORE_MAX;
        printf("Core gehiegi, makinaren maximoa aukeratu da: %d \n", CORE_MAX);
    }
    else if (core_kop < 1)
    {
        core_kop = 1;
        printf("Core gutxiegi, makinaren minimoa aukeratu da: 1 \n");
    }

    printf("Sartu makinaren Hardware hari kopurua: \n");
    scanf("%d", &hari_kop);

    if (hari_kop > TH_MAX)
    {
        hari_kop = TH_MAX;
        printf("Hardware hari gehiegi, makinaren maximoa aukeratu da: %d \n", TH_MAX);
    }
    else if (hari_kop < 1)
    {
        hari_kop = 1;
        printf("Hardware hari gutxiegi, makinaren minimoa aukeratu da: 1 \n");
    }

    printf("Sartu prozesuen sortze-periodoa (5000 - 15000 artean): \n");
    scanf("%d", &maiz_Pro);
    if (maiz_Pro < 5000)
    {
        maiz_Pro = 5000;
        printf("Periodo txikiegia, makinaren minimoa aukeratu da: 5000 \n");
    }
    else if (maiz_Pro > 15000)
    {
        maiz_Pro = 15000; 
        printf("Periodo handiegia, makinaren maximoa aukeratu da: 15000 \n");
    }

    printf("Sartu scheduler tenporizadorearen periodoa (20000 - 40000 artean): \n");
    scanf("%d", &maiz_Sch);
    if (maiz_Sch < 20000)
    {
        maiz_Sch = 20000;
        printf("Periodo txikiegia, makinaren minimoa aukeratu da: 20000 \n");
    }
    else if (maiz_Sch > 40000)
    {
        maiz_Sch = 40000;
        printf("Periodo handiegia, makinaren maximoa aukeratu da: 40000 \n");
    }

    printf("\n");

    printf("---------------KONFIGURAZIOA BUKATU DA----------------\n");

    printf("\n");

    printf("---------------EXEKUTATZEN----------------\n");

    printf("\n");

   // int th_balioa = CPU_kop * core_kop * hari_kop;

    CPU_Hasieratu(CPU_kop, core_kop, hari_kop);

    printf("\n");

    MemoriaHasieratu();

    AginduakKargatu();

    sleep(1);

    /*int i, j, k;

	for (i=0; i < CPU_kop; i++) {

		for (j=0; j < core_kop; j++) {

			for (k=0; k < hari_kop; k++) {
			
				Th_array[i][j][k] = hari;
				hari++; 
			}
		}
	}	

	int a,b,c;
	for (a=0; a < CPU_kop; a++) {

                for (b=0; b < core_kop; b++) {

                        for (c=0; c < hari_kop; c++) {

                                printf("%d %d %d = %lu\n", a,b,c,Th_array[a][b][c]); 
                        }
                }
        }   

        printf("\n");*/


    pthread_t erl, tenpProz, tenpSch;
	pthread_mutex_init(&mutexTick, NULL);
	pthread_cond_init(&condTick, NULL);
	pthread_cond_init(&condTick2, NULL);

    sem_init(&sem1, 0, 1);

    if (pthread_create(&erl, NULL, Erlojua, NULL) != 0) { 
		fprintf(stderr, "Errorea erlojuaren haria sortzen \n");
                exit(EXIT_FAILURE);
	}
	if (pthread_create(&tenpProz, NULL, Tenporizadorea_pro, maiz_Pro) != 0) { 
                fprintf(stderr, "Errorea prozesu tenporizadorearen haria sortzen \n");
                exit(EXIT_FAILURE); 
    }

	if (pthread_create(&tenpSch, NULL, Tenporizadorea_sch, maiz_Sch) != 0) { 
                fprintf(stderr, "Errorea Scheduler tenporizadorearen haria sortzen \n");
                exit(EXIT_FAILURE); 
    }

	if (pthread_join(erl, NULL) != 0) { 
                fprintf(stderr, "Errorea erl haria sinkronizatzean...\n");
                exit(EXIT_FAILURE);
    }

    if (pthread_join(tenpProz, NULL) != 0) { 
                fprintf(stderr, "Errorea tenpProz haria sinkronizatzean...\n");
                exit(EXIT_FAILURE); 
    }

	if (pthread_join(tenpSch, NULL) != 0) { 
                fprintf(stderr, "Errorea tenpSch haria sinkronizatzean...\n");
                exit(EXIT_FAILURE); 
    }
	
	pthread_mutex_destroy(&mutexTick);
	pthread_cond_destroy(&condTick);
	pthread_cond_destroy(&condTick2);
    sem_destroy(&sem1);

}