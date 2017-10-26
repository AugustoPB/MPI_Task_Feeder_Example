#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_TAREFAS 100  // Numero de tarefas no saco de trabalho
#define TAM_TAREFA 10000   // Tamanho de vetor a ser organizado pelos nodos

void initialize_matrix(int matrix[N_TAREFAS][TAM_TAREFA])
{
    int i,j;
    for(i=0; i<N_TAREFAS; i++)
        for(j=0; j<TAM_TAREFA; j++) matrix[i][j] = TAM_TAREFA-j;
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
 }

int main(int argc, char** argv)
{
    clock_t t1, t2;
    int (*tasks)[TAM_TAREFA] = malloc (N_TAREFAS * sizeof *tasks);
    initialize_matrix(tasks);

    t1 = clock();
    printf("Begin time: %lf\n", (double)t1/CLOCKS_PER_SEC);
    int i;
    for(i=0; i<N_TAREFAS; i++)
        qsort(tasks[i],TAM_TAREFA, sizeof(int), cmpfunc);

    t2 = clock();
    printf("Final time: %lf\n", (double)t2/CLOCKS_PER_SEC);
    printf("Run time: %lf\n", (double)(t2-t1)/CLOCKS_PER_SEC);


}
