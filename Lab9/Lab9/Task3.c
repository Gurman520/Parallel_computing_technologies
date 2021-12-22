#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
int rank;
int size;
int n, s = 0;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
if (rank == 0)
scanf("%d", &n);
MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
int* b = new int[n*2];
for (int i = 0; i < n*2; i++)
    b[i] = rank;
int* a = new int[size * size * 2 * n];
for (int i = 1; i < size; i++)
    a[i] = a[i - 1] + n;
MPI_Gather(b, 2*n, MPI_INT, a, 2*n, MPI_INT, 0, MPI_COMM_WORLD);
if (rank == 0) {
    printf("rank = %d a:\n", rank);
    for (int i = 0; i < size*2; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ",a[j+i*n]);
        printf("\n");
    }
}
MPI_Finalize();
return 0;
} 