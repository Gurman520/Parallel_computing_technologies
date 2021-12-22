#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include <math.h>

int main(int argc, char *argv[])
{
    int n = 10;
    int rank, count, size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start, end, sum1 = 0, sum2 = 0;
    for (int time = 3; time < 10; time++)
    { 
        start = MPI_Wtime();
        if (rank == 0)
        {
            double psum = 0;
            sum2 = 0;
            for (int i = 1; i < size; i++)
            {
                psum = 0;
                MPI_Recv(&psum, 1, MPI_DOUBLE, i, 777, MPI_COMM_WORLD, &stat);
                sum1 += psum;
            }
            end = MPI_Wtime();
            printf("Predel 10^%d, Summ = : %g. Time: %g\n", time, sum1, end - start);
        }
        else {
            sum2 = 0;
            for (int i = rank; i < pow(10, time); i += size)
            {
                sum2 += 1. / (i + 1); 
            }
            MPI_Send(&sum2, 1, MPI_DOUBLE, 0, 777, MPI_COMM_WORLD);
        }
    }


    MPI_Finalize();
    return 0;
} 