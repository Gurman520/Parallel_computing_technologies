#include <stdio.h>
#include "mpi.h"
#include "stdlib.h"


int main(int argc, char *argv[]){
    int rank;
    int size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        int* a = NULL;
        a = (int*)malloc(sizeof(int)*(size*3));
        for(int i = 0; i<3*size; i++)
        {
            a[i] = i;
        }
        for(int i = 0; i < 3*size; i += size)
        {
            for(int j = 1; j<size; ++j)
            {
                MPI_Send(&a[i+j], 1, MPI_INT, j, 777, MPI_COMM_WORLD);
            }
        }
    } else {
        int* b = NULL;
        b = (int*)malloc(sizeof(int)*3);
        for(int i = 0; i < 3; i++)
            MPI_Recv(&b[i], 1, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat);
        printf( "rank = %d, b: ",rank ); 
        for(int i = 0; i<3; i++)
            printf( "%d ", b[i] ); 
        printf( "\n " ); 
    }
    MPI_Finalize();
    return 0;
}
