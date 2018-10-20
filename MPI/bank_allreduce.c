#include<mpi.h>
#include<stdio.h>
#include <stdlib.h> 
#include <time.h> 
int main()
{
 MPI_Init(NULL,NULL);
 int rank, size, a[4], x, sum = 0;
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 for(int i = 0; i < 4; i++)
     a[i] = rand() % 10 + 1;
 MPI_Scatter(a,1,MPI_INT,&x,1,MPI_INT,0, MPI_COMM_WORLD);;
 MPI_Allreduce(&x,&sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
 printf("Bank Balace %d: %d\n",rank,sum);
 MPI_Finalize();
}