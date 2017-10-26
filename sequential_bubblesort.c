#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_TAREFAS 100  // Numero de tarefas no saco de trabalho
#define TAM_TAREFA 10000   // Tamanho de vetor a ser organizado pelos nodos

void bs(int n, int * vetor)
{
    int c=0, d, troca, trocou =1;

    while (c < (n-1) & trocou )
    {
        trocou = 0;
        for (d = 0 ; d < n - c - 1; d++)
            if (vetor[d] > vetor[d+1])
            {
                troca      = vetor[d];
                vetor[d]   = vetor[d+1];
                vetor[d+1] = troca;
                trocou = 1;
            }
        c++;
    }
}

void initialize_matrix(int matrix[N_TAREFAS][TAM_TAREFA])
{
    int i,j;
    for(i=0; i<N_TAREFAS; i++)
        for(j=0; j<TAM_TAREFA; j++) matrix[i][j] = TAM_TAREFA-j;
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
        bs(TAM_TAREFA, tasks[i]);

    t2 = clock();
    printf("Final time: %lf\n", (double)t2/CLOCKS_PER_SEC);
    printf("Run time: %lf\n", (double)(t2-t1)/CLOCKS_PER_SEC);


}
