#include "iostream"
#include <stdio.h>
#include "math.h"
#include "mpi.h"


int main(int argc, char* argv[])
{
    int rank;
    int size;
    double t1, t2;
    int buf;
    //float* buf = new float[10];
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 5)
    {
        buf = 3;
        /*
        for (int i = 0; i < 10; i++)
        buf[i] = 1.5;*/
    }
    t1 = MPI_Wtime();
    MPI_Bcast(&buf, 1, MPI_INT, 5, MPI_COMM_WORLD);
    //MPI_Bcast(buf, 10, MPI_FLOAT, 8, MPI_COMM_WORLD);
    t2 = MPI_Wtime();
    printf("rank = %d, buf = %d\n", rank, buf);
    //cout << "rank: " << rank << ", buf: " << buf[1] << " " << buf[2] << endl;
    //cout << "время выполнения: " << t2 - t1 << endl;
    printf("Time = %g\n", t2 - t1);
    MPI_Finalize();
    return 0;
}