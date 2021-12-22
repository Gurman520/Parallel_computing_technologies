#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
int rank;
int size;
int i, s = 0, j;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
int* b = new int[size];
for (i = 0; i < rank + 1; i++)
    b[i] = rank;
int** a = new int* [size * 2];
a[0] = new int[size * size * 2];
for (i = 1; i < size * 2; i++)
    a[i] = a[i - 1] + size;
for (i = 0; i < size * 2; i++) {
    for (j = 0; j < size; j++) {
        a[i][j] = -1;
    }
}
int* ds = new int[size];
for (int i = 0; i < size; i++)
    ds[i] = (i * size) + i;
for (int l = 0; l < 2; l++) {
    int* dl = new int[size];
    int* ds = new int[size];
    for (int i = 0; i < size; i++)
    {
        dl[i] = i + 1;
        ds[i] = (i * size * 2) + l * size;
    }
    MPI_Gatherv(b, rank + 1, MPI_INT, *a, dl, ds, MPI_INT, 0, MPI_COMM_WORLD);
}
    if (rank == 0){
        printf("rank= %d a:\n", rank);
        for (i = 0; i < size * 2; i++) {
            for (j = 0; j < size; j++)
                printf("%d ", a[i][j]);
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}