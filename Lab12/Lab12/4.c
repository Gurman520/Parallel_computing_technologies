#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double t1, t2;
    int n, *s;
    MPI_Datatype MPI_Mytype;
    for (int i = 3; i < 10; i++)
    {
        n = pow(10, i);
        s = new int[n];
        MPI_Type_vector(n / 2, 1, 2, MPI_INT, &MPI_Mytype);
        MPI_Type_commit(&MPI_Mytype);
        if (rank == 0)
        {
            for (int i = 0; i < n; i++)
            {
                s[i] = rank;
            }
            t1 = MPI_Wtime();
            MPI_Send(s, 1, MPI_Mytype, 1, 777, MPI_COMM_WORLD);
            MPI_Recv(s, 1, MPI_Mytype, 1, 777, MPI_COMM_WORLD, &status);
            t2 = MPI_Wtime();
            printf("Size: 10^%d Time: %lf\n", i, (t2 - t1) / 2);
        }
        else
        {
            MPI_Recv(s, 1, MPI_Mytype, 0, 777, MPI_COMM_WORLD, &status);
            MPI_Send(s, 1, MPI_Mytype, 0, 777, MPI_COMM_WORLD);
        }
        t1 = 0;
        t2 = 0;
        delete s;
    }
    MPI_Finalize();
    return 0;
}