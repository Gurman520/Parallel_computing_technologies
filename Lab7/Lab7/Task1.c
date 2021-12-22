#include <stdio.h>
#include "mpi.h"
#include "iostream"
using namespace std;

int main(int argc, char *argv[])
{
    int rank;
    int size;
    int a = 0;
    MPI_Init(&argc, &argv);
    MPI_Status stat;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0)
    {
        MPI_Sendrecv(&rank, 1, MPI_INT, 2, 777, &a, 1, MPI_INT, (size-2), 777, MPI_COMM_WORLD, &stat);
        cout << "rank = " << rank << " A = " << a << endl;
    }
    if(rank == 1)
    {
        MPI_Sendrecv(&rank, 1, MPI_INT, 3, 777, &a, 1, MPI_INT, (size-1), 777, MPI_COMM_WORLD, &stat);
        cout << "rank = " << rank << " A = " << a << endl;
    }
    else if(rank == size-1)
    {
        MPI_Sendrecv(&rank, 1, MPI_INT, 1, 777, &a, 1, MPI_INT, (rank-2), 777, MPI_COMM_WORLD, &stat);
        cout << "rank = " << rank << " A = " << a << endl;
    }
    else if(rank == size-2)
    {
        MPI_Sendrecv(&rank, 1, MPI_INT, 0, 777, &a, 1, MPI_INT, (rank-2), 777, MPI_COMM_WORLD, &stat);
        cout << "rank = " << rank << " A = " << a << endl;
    }
    else{
        MPI_Sendrecv(&rank, 1, MPI_INT, (rank+2), 777, &a, 1, MPI_INT, (rank-2), 777, MPI_COMM_WORLD, &stat);
        cout << "rank = " << rank << " A = " << a << endl;
    }
    MPI_Finalize();
    return 0;
} 