#include <stdio.h> 
#include "mpi.h" 
int main(int argc, char *argv[])  { 
    int rank; 
    int size; 
    int n,i,s=0; 
    MPI_Status stat; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    if(rank==0) scanf("%d",&n); 
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD); 
    int *a=new int[2*n*size]; 
    for(i=0;i<2*n*size;i++) 
        a[i]=rank+i; 
    int *b=new int[2*n]; 
    int *rc=new int[size]; 
    for(i=0;i<size;i++) 
        rc[i]=2*n; 
    MPI_Reduce_scatter(a,b,rc,MPI_INT,MPI_SUM,MPI_COMM_WORLD); 
    for(i=0; i<100000000*rank; i++) 
        s+=1; 
    printf("rank= %d  b: ",rank); 
    for(i=0;i<2*n;i++) 
    printf(" %d ", b[i]); 
    printf("\n "); 
    MPI_Finalize(); 
    return 0; 
}