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
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD); 
    int **a=new int *[n]; 
    a[0]=new int [n*n]; 
        for(i=1; i<n; i++) 
            a[i]=a[i-1]+n; 
    if(rank==0) { 
        for(i=0;i<n;i++) 
            for(j=0;j<n;j++) 
                a[i][j]=i; 
    }
    int cel = n / size; 
    int ostat = n % size;
    int rezerv = ostat;
    int *RC = new int[size]; 
    int *ds = new int [size];
    int *X = new int [size]; 
    for (int i=0;i<size;i++) { 
        if (ostat != 0) { 
            ds[i] = n * i * (cel + 1);
            ostat--;
            RC[i] = n * (cel + 1);
            X[i] = cel + 1;
        }
        else {
            if (i == rezerv) {
                RC[i] = n * cel;
                ds[i] = ds[i-1] + (cel * n) + n;
                X[i] = cel;
            }
            else {
                RC[i] = n * cel; 
                ds[i] = ds[i-1] + (cel * n);
                X[i] = cel;
            }
        } 
    } 
    int **b=new int *[X[rank]]; 
    b[0]=new int [X[rank]*n]; 
    for(i=1; i<X[rank]; i++) 
        b[i]=b[i-1]+n; 
    MPI_Scatterv(*a,RC,ds,MPI_INT,*b,X[rank] * n,MPI_INT,0,MPI_COMM_WORLD); 
    for(i=0; i<100000000*rank; i++) 
    s+=1; 
    printf("rank= %d  b: \n",rank); 
    for(i=0; i<X[rank]; i++) 
    { 
        for(j=0;j<n;j++) 
            printf(" %d ",b[i][j]); 
        printf("\n"); 
    } 
    MPI_Finalize(); 
    return 0; 
} 