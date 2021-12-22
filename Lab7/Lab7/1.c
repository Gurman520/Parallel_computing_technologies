#include <stdlib.h> 
#include "mpi.h" 
#include "iostream" 
 
int main(int argc, char *argv[]) 
{ 
    int rank; 
    int size; 
    int a; 
    double t1, t2; 
    MPI_Status stat; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    
    if(rank==0)  
    { 
        a = 5; 
        t1 = MPI_Wtime(); 
        _sleep(1); 
        MPI_Send(&a, 1, MPI_INT, 1, 777, MPI_COMM_WORLD); 
        t2 = MPI_Wtime(); 
        printf("rank: %d, time: %f\n", rank, t2 - t1); 

    } 
    if(rank==1)  
    { 
        t1 = MPI_Wtime(); 
        MPI_Recv(&a, 1, MPI_INT, 0, 777, MPI_COMM_WORLD, &stat); 
        t2 = MPI_Wtime(); 
        printf("rank: %d, time: %f a=%d\n",rank,t2-t1,a); 
    } 
    MPI_Finalize(); 
    return 0; 
}