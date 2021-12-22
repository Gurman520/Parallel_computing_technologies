#include <stdio.h> 
#include "mpi.h" 

int main(int argc, char *argv[]) {
    int rank; 
    int size; 
    int i,s=0; 
    MPI_Status stat; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    int *a=new int[size*(size+1)]; 
    if(rank==0) 
        for(i=0; i<size*(size+1); i++) 
           a[i]=i; 
    int *b=new int [rank + rank + 2]; 
    int *RC = new int[size]; 
    int *ds = new int [size];
    RC[0] = 2; ds[0] = 0;
    for(int i=1;i<size;i++) { 
         RC[i]=RC[i-1] + 2; 
         ds[i]=i*(i+1);
    } 
    MPI_Scatterv(a,RC,ds,MPI_INT,b,(rank + rank + 2),MPI_INT,0,MPI_COMM_WORLD); 
    for(i=0; i<100000000*rank; i++) 
    s+=1; 
    printf("rank= %d  b: ",rank); 
    for(i=0; i<rank + rank + 2; i++) 
        printf("  %d  ",b[i]); 
    printf("\n "); 
    MPI_Finalize(); 
    return 0; 
}