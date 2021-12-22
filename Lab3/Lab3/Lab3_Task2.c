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

    if (rank != 0) {
        int* a = NULL;
        a = (int*)malloc(sizeof(int)*(rank+1));
        for (int i = 0; i < rank+1; i++) {
            a[i] = rank;
        }
        MPI_Send(&a[0], rank+1, MPI_INT, 0, 777, MPI_COMM_WORLD);
    }
    else {
        int count = 0;
        int sum = 0;
        for (int i = size; i > 1; i--)
            sum += i;
        int* b = NULL;
        b = (int*)malloc(sizeof(int)*(sum));
        for (int i = 0; i<size-1; ++i)
        {
            MPI_Recv(&b[count], i+2, MPI_INT, i + 1, 777, MPI_COMM_WORLD, &stat); 
            count += i+2;
        }
            
        for(int i = 0; i< sum; i++)
            printf( "%d, ", b[i] ); 
    }

    MPI_Finalize();
    return 0;
}
