#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
int main()
{
 MPI_Init(NULL,NULL);
 int rank, size, a[4], x, sum=0;
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 for(int i = 0; i < 4; i++)
     a[i] = rand() % 100 + 1;
 MPI_Scatter(a,1,MPI_INT,&x,1,MPI_INT,0, MPI_COMM_WORLD);
 printf("Local Bank Balance for account holder %d: %d\n",rank,x);
 MPI_Reduce(&x,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
 if(rank==0)
 printf("Bank Balace: %d\n",sum);
 MPI_Finalize();
}