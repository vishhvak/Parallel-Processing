#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  MPI_Init (&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int number, flag;

  if (rank == 0) {
    
    printf("Process %d inputting number and sending it\n", rank);
    printf("Enter the number to be sent\n");
    scanf("%d",&number);
    
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  } 

  else if (rank == 1) {
    
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received number %d from process 0\n", rank, number);
    if(number%2==0) 
      flag = 1;
    else 
      flag = 0;
    MPI_Send(&flag, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
  }

  else if(rank == 2) {

    MPI_Recv(&flag, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received flag %d from process 0\n", rank, flag);
    if(flag == 1) 
      printf("Number received is even\n");
    else if(flag == 0)
      printf("Number received is odd\n");
  }

  MPI_Finalize();
}