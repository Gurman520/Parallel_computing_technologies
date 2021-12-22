#include <stdio.h> 
#include "mpi.h" 
int main(int argc, char *argv[]) 
{ 
int rank; 
int size; 
int i,s=0; 
MPI_Status stat; 
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
MPI_Comm_size(MPI_COMM_WORLD, &size); 
int *b=new int [size-rank]; 
for(i=0;i<size-rank;i++) 
b[i]=rank; 
int *a=new int[(size*(size+1))/2]; 
int *dl = new int[size]; 
int *ds = new int [size]; 
int n = 0;
for (int i=0;i<size;i++) 
{ 
    dl[i]=size - i; 
    ds[i]=n;
    n += RC[i];
} 
MPI_Gatherv(b,size-rank,MPI_INT,a,dl,ds,MPI_INT,0,MPI_COMM_WORLD); 
for(i=0; i<100000000*rank; i++) 
s+=1; 
printf("rank= %d  a: ",rank); 
for(i=0; i<(size*(size+1))/2; i++) 
printf("  %d  ",a[i]); 
printf("\n "); 
MPI_Finalize(); 
return 0; 
}