#include <stdio.h> 
#include "mpi.h" 

int main(int argc, char *argv[]) { 
    int rank; 
    int size; 
    int i,j,s=0; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    int *a=new int [2*size]; 
    if(rank==0)
        for(i=0;i<2*size;i++) 
            a[i]=i; 
    int *b=new int[2]; 
    MPI_Scatter(a,2,MPI_INT,b,2,MPI_INT,0,MPI_COMM_WORLD); 
    for(i=0; i<100000000*rank; i++) 
        s+=1; 
    printf("rank= %d  a: ",rank); 
    for(i=0; i<2; i++) 
        printf(" %d ",b[i]); 
    printf("\n"); 
    MPI_Finalize(); 
    return 0; 
}