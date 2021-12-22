#include <stdio.h> 
#include "mpi.h" 
int main(int argc, char *argv[]) 
{ 
    int rank; 
    int size; 
    int n=0,i,s=0; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    int *a=new int[size]; 
    MPI_Gather(&rank,1,MPI_INT,a,1,MPI_INT,0,MPI_COMM_WORLD); 
    for(i=0; i<100000000*rank; i++) 
        s+=1; 
    printf("rank= %d  a: ",rank); 
    for(i=0; i<size; i++) 
    printf(" %d ",a[i]); 
    printf("\n "); 
    MPI_Finalize(); 
    return 0; 
}