#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double t1, t2;
    int n, *s, *s1;
    for (int i = 3; i < 10; i++)
    {
        n = pow(10, i);
        s = new int[n];
        s1 = new int[n / 2];
        if (rank == 0)
        {
            for (int i = 0; i < n; i++)
            {
                s[i] = rank;
            }
            t1 = MPI_Wtime();
            for (int i = 0, x = 0; i < n; i += 2, x++)
            {
                s1[x] = s[i];
            }
            MPI_Send(s1, n / 2, MPI_INT, 1, 777, MPI_COMM_WORLD);
            MPI_Recv(s1, n / 2, MPI_INT, 1, 777, MPI_COMM_WORLD, &stat);
            t2 = MPI_Wtime();
            printf("Size: 10^%d Time: %lf\n", i, (t2 - t1) / 2);
        }
        else
        {
            MPI_Recv(s1, n / 2, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat);
            for (int i = 0, x = 0; i < n; i += 2, x++)
            {
                s[i] = s1[x];
            }
            MPI_Send(s1, n / 2, MPI_INT, 0, 777, MPI_COMM_WORLD);
        }
        delete s;
        delete s1;
    }
    MPI_Finalize();
    return 0;
}