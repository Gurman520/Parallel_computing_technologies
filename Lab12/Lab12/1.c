#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size; 
    MPI_Status stat; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    double t1,t2; 
    int n,*a; 
    for (int i=3;i<10;i++) { 
        n = pow(10,i); 
        a = new int[n]; 
        if (rank==0) { 
            for (int i=0;i<n;i++) { 
                a[i]=rand(); 
        }
        t1=MPI_Wtime(); 
        MPI_Send(a, n, MPI_INT, 1, 777, MPI_COMM_WORLD); 
        MPI_Recv(a, n, MPI_INT, 1, 777, MPI_COMM_WORLD, &stat);
        t2=MPI_Wtime(); 
        printf("Size: 10^%d Time: %lf\n", i, (t2-t1)/2);
        } 
    else { 
        MPI_Recv(a, n, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat); 
        MPI_Send(a, n, MPI_INT, 0, 777, MPI_COMM_WORLD); 
    } 
    delete a; 
    }
    MPI_Finalize();
    return 0;
}