#include <stdio.h>
#include "mpi.h"
#include "stdlib.h"
#include "iostream"
#include <time.h>

int main(int argc, char *argv[]){
    int rank;
    int size, count;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        int** a = new int*[size];
        a[0] = new int[size*size];
        for (int i = 1; i < size; i++)
            a[i] = a[i-1] + size;
        for (int i = 0 ; i < size; i++){
            for (int j = 0 ; j < size; j++){
                a[i][j] = 0;
            }
        }
        for (int i = 1; i < size; i++)
        {
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat);
            MPI_Get_count(&stat, MPI_INT, &count);
            MPI_Recv(a[stat.MPI_SOURCE], count, MPI_INT, stat.MPI_SOURCE, 777, MPI_COMM_WORLD, &stat);
        }  
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++){
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }        
    }
    else
    {
        srand(time(NULL) % (rank+465));
        int z = rand() % size;
        int * b = new int[z];
        printf("rank = %d, b =", rank);
        for (int i = 0; i < z; i++)
        {
            b[i] = rank;
            printf("%d", b[i]);
        }
        printf("\n");
        MPI_Send(b, z, MPI_INT, 0, 777, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}