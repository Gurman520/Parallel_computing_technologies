#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int rank, size, n = 10;
    MPI_Init(&argc, &argv);
    MPI_Status stat;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Datatype mt, mt1;
    MPI_Type_vector(n, 1, n, MPI_INT, &mt);
    MPI_Type_commit(&mt);
    MPI_Type_create_hvector(n/2, 1, 8, mt, &mt1);
    MPI_Type_commit(&mt1);

    int** a = new int* [n];
    a[0] = new int[n*n];
    for (int i = 1; i < n; i++)
        a[i] = a[i - 1] + n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
    if (rank == 0){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = 10 * (i + 1) + (j + 1);
        MPI_Send(&a[0][1], 1, mt1, 1, 111, MPI_COMM_WORLD);
    }
    if (rank == 1){
        MPI_Recv(&a[0][1], 1, mt1, 0, 111, MPI_COMM_WORLD, &stat);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)
                printf("%3d ", a[i][j]);
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
