#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
int rank;
int size;
int n=9,i,j,s=0;
MPI_Status stat;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Datatype mt;
MPI_Type_vector(n,1,n,MPI_INT,&mt);
MPI_Type_commit(&mt);
int **b=new int *[n];
b[0]=new int[n*n];
for(i=1;i<n;i++)
b[i]=b[i-1]+n;
for(i=0;i<n;i++)
for(j=0;j<n;j++)
b[i][j]=0;
if(rank==0)
{
for(i=0;i<n;i++)
for(j=0;j<n;j++)
b[i][j]=10*(i+1)+j+1;
MPI_Send(*b,1,mt,1,777,MPI_COMM_WORLD);
}
if(rank==1)
{
MPI_Recv(*b,n,MPI_INT,0,777,MPI_COMM_WORLD,&stat);
}
for(i=0; i<100000000*rank; i++)
s+=1;
printf("rank= %d b: \n",rank);
for(i=0; i<n; i++)
{
for(j=0;j<n;j++)
printf(" %d ",b[i][j]);
printf("\n");
}
MPI_Finalize();
return 0;
}