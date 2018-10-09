#include <stdio.h>
#include <string.h> 
#include "mpi.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
  int num[4], m[4];
  int  i, j, rank, size, temp;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  for(i=0;i<4;i++)
        num[i]= (rand() % 100 + 1);

  MPI_Gather(&num[rank],1,MPI_INT,m,1,MPI_INT,0,MPI_COMM_WORLD);

  if(rank == 0) {
      printf("The 4 numbers received are\n");
      for(i=0;i<4;i++)
        printf("%d\n",m[i]);
      for(i=0;i<4;i++)
      {
          for(j=i+1;j<4;j++) 
          {
              if(m[i]>m[j])
              {
                  temp = m[i];
                  m[i] = m[j];
                  m[j] = temp;
              }
          }
      }
      printf("The 4 numbers after sorting are are\n");
      for(i=0;i<4;i++)
        printf("%d\n",m[i]);
  }

  MPI_Finalize();
}