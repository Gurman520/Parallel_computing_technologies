#include <stdio.h>
#include "mpi.h"
#include "stdlib.h"
#include <iostream>


int main(int argc, char *argv[]){
    int rank;
    int size;
    int n = 10;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    

    if (rank == 0)
    {
        int **a = new int *[size];
        a[0] = new int[size*size];
        for (int i = 1; i < size; i++)
            a[i] = a[i-1] + size;
        for (int i = 0 ; i < size; i++){
            for (int j = 0 ; j < size; j++){
                a[i][j] = i;
            }
        }
        for (int i = 1; i < size; i++)
            MPI_Send(&a[i][0], size, MPI_INT, i, 777, MPI_COMM_WORLD);
    }
    else
    {
        int *b = new int[size];
        MPI_Recv(&b[0], size, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat); 
        printf("rank = %d", rank);
        for (int i = 0; i < size; i++)
            printf(" %d, ", b[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
