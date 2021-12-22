#include <stdio.h> 
#include "mpi.h" 
int main(int argc, char *argv[]) { 
    int rank; 
    int size; 
    int n,i,s=0, j; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    if(rank==0) scanf("%d",&n);
    int **a=new int *[2*size]; 
    a[0]=new int [2*n*size]; 
        for(i=1; i<2*size; i++) 
            a[i]=a[i-1]+n; 
    if(rank==0) { 
        for(i=0;i<2*size;i++) 
            for(j=0;j<n;j++) 
                a[i][j]=i; 
    }
    int **b=new int *[2]; 
    b[0]=new int [(rank+1)*2]; 
    for(i=1; i<2; i++) 
        b[i]=b[i-1]+(rank+1); 
    int *RC = new int[size]; 
    int *ds = new int [size]; 
        for (int i=0;i<size;i++) 
    { 
     RC[i]=2* (i + 1); 
     ds[i]=2*n*i; 
    } 
    MPI_Scatterv(*a,RC,ds,MPI_INT,*b,(rank+1)*2,MPI_INT,0,MPI_COMM_WORLD); 
    for(i=0; i<100000000*rank; i++) 
    s+=1; 
    printf("rank= %d  b: \n",rank); 
    for(i=0; i<2; i++) 
    { 
        for(j=0;j<rank+1;j++) 
            printf(" %d ",b[i][j]); 
        printf("\n"); 
    } 
    MPI_Finalize(); 
    return 0; 
} 