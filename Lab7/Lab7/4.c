#include <stdio.h> 
#include "mpi.h" 
#include "iostream" 
#include <unistd.h>

int main(int argc, char *argv[]) 
{ 
int rank; 
int size; 
int a,k=0,fl=0; 
double t1, t2,t3; 
  MPI_Status stat; 
  MPI_Request req; 
  MPI_Init(&argc, &argv); 
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &size); 
   
  if(rank==0)  
  { 
      a = 5; 
      t1 = MPI_Wtime(); 
      sleep(1); 
      MPI_Send(&a, 1, MPI_INT, 1, 777, MPI_COMM_WORLD); 
      t2 = MPI_Wtime(); 
      printf("rank: %d, time: %f\n", rank, t2 - t1); 
   } 
  if(rank==1)  
  { 
      t1 = MPI_Wtime(); 
      MPI_Irecv(&a, 1, MPI_INT, 0, 777, MPI_COMM_WORLD, &req); 
      t2 = MPI_Wtime(); 
      while(fl==0) 
      { 
      k++; 
      MPI_Test(&req,&fl,&stat); 
      } 
      t3 = MPI_Wtime(); 
      printf("rank: %d, time Irecv: %f time Test: %f k=%d a=%d\n",rank,t2-t1,t3-t2,k,a); 
  } 
  MPI_Finalize(); 
  return 0; 
  }