
#include "mpi.h"
#include "stdlib.h"
#include <stdio.h>
#include "math.h"

int main(int argc, char *argv[])
{
    int rank;
    int size;
    double t1, t2, sum = 0;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (int j = 3; j < 10; j++)
    {
        sum = 0;
        t1 = MPI_Wtime();
        for (int i = 0; i < pow(10, j); i++)
        {
            sum += 1. / (i + 1); 
        }
        t2 = MPI_Wtime();
        printf("Predel 10^%d, sum = %g, time = %g\n",j,  sum, t2-t1);
    }
    MPI_Finalize();
    return 0;
}
