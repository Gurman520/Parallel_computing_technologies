#include <stdio.h>
#include "math.h"
#include "mpi.h"

void bcast(void*, int, MPI_Datatype, int, int, int);

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
    bcast(&buf, 1, MPI_INT, 5, rank, size);
    //bcast(buf, 10, MPI_FLOAT, 5, rank, size);
    t2 = MPI_Wtime();
    printf("rank = %d, buf = %d\n", rank, buf);
    //cout << "rank: " << rank << ", buf: " << buf[1] << " " << buf[2] << endl;
    //cout << "время выполнения: " << t2 - t1 << endl;
    printf("Time = %g\n", t2 - t1);
    MPI_Finalize();
    return 0;
}

void bcast(void* buf, int n, MPI_Datatype type, int root, int rk, int sz)
{
    MPI_Status stat1;
    int R;
    if (rk == root)
    {
        for (int i = 0; i < log(sz) / log(2); i++)
        {
            R = pow(2, i) + rk;
            if (R > sz - 1)
                R = R - sz - 1;
            MPI_Send(buf, n, type, R, 777, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(buf, n, type, MPI_ANY_SOURCE, 777, MPI_COMM_WORLD, &stat1);
        for (int i = 0; i < log(sz) / log(2); i++)
        {
            R = pow(2, i) + rk;
            if (R > sz - 1)
                R = R - sz - 1;
            MPI_Send(buf, n, type, R, 777, MPI_COMM_WORLD);
        }
    }
}