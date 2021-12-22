#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])

{
    int rank;
    int size;
    int s = 0, n = 10;
    MPI_Status stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int count = 0, z = -3, x = 0;
    while (z < (n + (n-1))) {
        z += 4;
        count += 1;
    }
    z = -3;
    int* bl=new int[count];
    int* ds=new int[count];
    for (int i = 0; i < count; i++) {
        z += 4;
        bl[i] = z;
        ds[i] = x;
        x += n + n - 2;
        //printf("%d - %d\n", bl[i], ds[i]);
    }
    if (bl[count - 1] + ds[count - 1] > n*n)
        bl[count - 1] = n;
    // bl[count - 1] = z + 4;
    // ds[count - 1] = n;
    //int bl[5] = {1, 5, 9, 13, 17};
    //int ds[5] = {0, 16, 32, 48, 64};
    MPI_Datatype mt;
    MPI_Type_indexed(count, bl, ds, MPI_INT, &mt);
    MPI_Type_commit(&mt);
    int **b = new int *[n];
    b[0] = new int[n * n];
    for (int i = 1; i < n; i++)
        b[i] = b[i - 1] + n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i][j] = 0;
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                b[i][j] = 10 * (i + 1) + j + 1;
        MPI_Send(*b, 1, mt, 1, 777, MPI_COMM_WORLD);
    }
    if (rank == 1)
    {
        MPI_Recv(*b, 1, mt, 0, 777, MPI_COMM_WORLD, &stat);
    }
    for (int i = 0; i < 100000000 * rank; i++)
        s += 1;
    printf("rank = %d\n", rank);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%3d ", b[i][j]);
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}