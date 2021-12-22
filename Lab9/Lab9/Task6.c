#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rank;
    int size;
    int s = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int* b = new int[size];
    int di = size - (size - rank);
    int** mas = new int* [size];
    int* mas1 = new int[size];
    int* mas2 = new int[size];
    for (int i = 0; i < di; i++)
        b[i] = 0;
    for (int i = di; i < size; i++)
        b[i] = rank;
    mas[0] = new int[size * size];
    for (int i = 1; i < size; i++)
        mas[i] = mas[i - 1] + size;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            mas[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++) {
        mas1[i] = size;
        mas2[i] = i * size;
    }
    MPI_Gatherv(b, size, MPI_INT, *mas, mas1, mas2, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("rank = %d\n", rank);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                printf("%d ", mas[i][j]);
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
