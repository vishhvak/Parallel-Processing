#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int power(int digit, int count) {
  int p = 1;
  for(int i =0; i<count; i++)
    p = p*digit;
  return p;
}

int main(int argc, char** argv) {

  MPI_Init (&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int number,flag;
  if (rank == 0) {
    
    printf("Process %d inputting number and sending it\n", rank);
    printf("Enter the number to be sent\n");
    scanf("%d",&number);
    
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    MPI_Send(&number, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    MPI_Send(&number, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
  } 

  else if (rank == 1) {
    
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received number %d from process 0\n", rank, number);
    
    //Even/Odd Routine
    if(number%2==0)
      flag = 0;
    else
      flag = 1;

    MPI_Send(&flag, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
  }

  else if (rank == 2) {

    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //Check if Prime/Composite Routine
    int f = 0;
    for(int i = 2; i < number/2; i++)
    {
      if(number%i==0)
      {
        f = 1;
        flag = 0;
        break;
      }
    }
    if(f == 0)
      flag = 1;

    MPI_Send(&flag, 1, MPI_INT, 5, 0, MPI_COMM_WORLD);
  }

  else if (rank == 3) {
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    int count=0,sum = 0;
    int n1,n2,digit;
    n1 = n2 = number;
    while(n1 > 0) {
      ++count;
      n1 = n1/10;
    }
    for (int i =0; i < count; i++)
    {
      digit = n2%10;
      sum += power(digit,count); 
      n2 = n2/10;
    }
    if(number == sum)
      flag = 0;
    else
      flag = 1;
    MPI_Send(&flag, 1, MPI_INT, 6, 0, MPI_COMM_WORLD);
  }

  else if(rank == 4) {

    MPI_Recv(&flag, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received flag %d from process 0\n", rank, flag);
    if(flag == 0) 
      printf("Number received is even\n");
    else if(flag ==1)
      printf("Number received is odd\n");
  }

  else if(rank == 5) {

    MPI_Recv(&flag, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received flag %d from process 0\n", rank, flag);
    if(flag == 0)
      printf("Number received is composite\n");
    else if(flag == 1) 
      printf("Number received is prime\n");
  }

  else if(rank == 6) {

    MPI_Recv(&flag, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received flag %d from process 0\n", rank, flag);
    if(flag == 0) 
      printf("Number received is an armstrong number\n");
    else if(flag == 0)
      printf("Number received is not an armstrong number\n");
  }

  MPI_Finalize();
}