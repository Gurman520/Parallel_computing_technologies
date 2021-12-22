#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int rank;
    int size;
    int *a, *b, n = 4;
    double t1, t2;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
    {
        int *a = new int[n];
        for(int i = 0; i<n; i++)
        {
            a[i] = i;
        }
        int *b = new int[n];
        t1 = MPI_Wtime();
        MPI_Send(&a[0], n, MPI_INT, 1, 777, MPI_COMM_WORLD);
        MPI_Recv(&b[0], n, MPI_INT, 1, 777, MPI_COMM_WORLD, &stat);
        t2 = MPI_Wtime();
        printf("rank = %d, time = %f\n b: ", rank, t2 - t1);
        for(int i = 0; i<n; i++)
            printf("%d ", b[i]);
    }
    if(rank==1)
    {
        int *b = new int[n];
        for(int i = 0; i<n; i++)
        {
            b[i] = i*10;
        }
        int *a = new int[n];
        t1 = MPI_Wtime();
        MPI_Send(&b[0], n, MPI_INT, 0, 777, MPI_COMM_WORLD);
        MPI_Recv(&a[0], n, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat);
        t2 = MPI_Wtime();
        printf("rank = %d, time = %f\n a: ", rank, t2 - t1);
        for(int i = 0; i<n; i++)
            printf("%d ", a[i]);
    }
    MPI_Finalize();
    return 0;
}