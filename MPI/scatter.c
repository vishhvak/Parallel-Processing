#include <stdio.h>
#include <string.h> 
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
  int num[16];
  int  i, rank, size;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0)
  {
    for(i=0;i<16;i++)
        num[i]=i;
  }
  
  int *rec = malloc(sizeof(int) * 4);

  MPI_Scatter(num,4,MPI_INT,rec,4,MPI_INT,0,MPI_COMM_WORLD);
  for(i=0;i<4;i++)
    printf( "Number from process %d : %d\n", rank, rec[i]);

  MPI_Finalize();
}