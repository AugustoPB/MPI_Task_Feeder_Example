#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

#define TASK_TAG 1
#define FINISH_TAG 2

#define N_TAREFAS 10  // Numero de tarefas no saco de trabalho
#define TAM_TAREFA 1000   // Tamanho de vetor a ser organizado pelos nodos

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
    for(int i=0; i<N_TAREFAS; i++)
        for(int j=0; j<TAM_TAREFA; j++) matrix[i][j] = TAM_TAREFA-j;
}

int main(int argc, char** argv)
{
    int my_rank;       // Identificador deste processo
    int proc_n;        // Numero de processos disparados pelo usuário na linha de comando (np)
    MPI_Status status; // estrutura que guarda o estado de retorno

    MPI_Init(&argc , &argv); // funcao que inicializa o MPI, todo o código paralelo esta abaixo

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);  // pega pega o numero do processo atual (rank)
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n); // pega informação do numero de processos (quantidade total)

    if ( my_rank == 0 ) // qual o meu papel: sou o mestre ou um dos escravos?
    {   // papel do mestre

        int *org_vector = malloc(proc_n* sizeof(int));
        int remaning_tasks = N_TAREFAS;
        int completed_tasks = 0;
        int tasks[N_TAREFAS][TAM_TAREFA];
        initialize_matrix(tasks);

        // first iteration
        for(int i=1; (i<proc_n)&&(remaning_tasks > proc_n-1); i++)
        {
            MPI_Send(tasks[N_TAREFAS-remaning_tasks], TAM_TAREFA, MPI_INT, i, TASK_TAG, MPI_COMM_WORLD);
            org_vector[i] = N_TAREFAS-remaning_tasks;
            remaning_tasks--;
        }

        while(completed_tasks < N_TAREFAS)
        {
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(tasks[org_vector[status.MPI_SOURCE]], TAM_TAREFA, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            completed_tasks++;

            if(remaning_tasks)
            {
                MPI_Send(tasks[N_TAREFAS-remaning_tasks], TAM_TAREFA, MPI_INT, status.MPI_SOURCE, TASK_TAG, MPI_COMM_WORLD);
                org_vector[status.MPI_SOURCE] = N_TAREFAS-remaning_tasks;
                remaning_tasks--;
            }
            else
            {
                MPI_Send(&completed_tasks, 1, MPI_INT, status.MPI_SOURCE, FINISH_TAG, MPI_COMM_WORLD);
            }

        }

       /*
       memset(saco,0,sizeof(saco));

       int i;
       for ( i=0 ; i < 7 ; i++) // mando o trabalho para os escravos fazerem
        {
            printf("%d\n %d\n", messag[0][i], messag[2][i]);
        message = saco[i];
        MPI_Send(&message, 1, MPI_INT, i+1, 1, MPI_COMM_WORLD);  // envio trabalho saco[i] para escravo com id = i+1;
        }
        // recebo o resultado

        for ( i=0 ; i < 7 ; i++)
        {
        // recebo mensagens de qualquer emissor e com qualquer etiqueta (TAG)

        MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); // recebo por ordem de chegada com any_source
        printf("mess: %d", message);
        saco[status.MPI_SOURCE-1] = message;   // coloco mensagem no saco na posição do escravo emissor
        }
        */
    }
    else
    {// papel do escravo

        int message[TAM_TAREFA];

        while(1)
        {
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if(status.MPI_TAG == FINISH_TAG)
            {
                MPI_Finalize();
                return 0;
            }

            MPI_Recv(message, TAM_TAREFA, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);    // recebo do mestre

            printf("sorting : %d\n", message[10]);
            bs(TAM_TAREFA, message);
            printf("sorted : %d\n", message[10]);

            MPI_Send(message, TAM_TAREFA, MPI_INT, 0, TASK_TAG, MPI_COMM_WORLD);

        }


        //message = message+1;      // icremento conteúdo da mensagem

        //MPI_Send(&message, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);    // retorno resultado para o mestre
     }
     MPI_Finalize();

}
