#include <stdio.h>
#include <string.h> 
#include "mpi.h"
#include <stdlib.h>
#include <math.h>

void nname(int n) {
    int num = 0, digits;
    digits = (int) log10(n); 

    while(n != 0)
    {
        num = (num * 10) + (n % 10);
        n /= 10;
    }
    digits =  digits - ((int) log10(num));  

    while(num != 0)
    {
        switch(num % 10)
        {
            case 0: 
                printf("Zero");
                break;
            case 1: 
                printf("One ");
                break;
            case 2: 
                printf("Two ");
                break;
            case 3: 
                printf("Three ");
                break;
            case 4: 
                printf("Four ");
                break;
            case 5: 
                printf("Five ");
                break;
            case 6: 
                printf("Six ");
                break;
            case 7: 
                printf("Seven ");
                break;
            case 8: 
                printf("Eight ");
                break;
            case 9: 
                printf("Nine ");
                break;
        }
        printf(" ");
        num /= 10;
    }
    
    while(digits)
    {
        printf("Zero ");
        digits--;
    }
}


int main(int argc, char **argv)
{
  int num1[16], num;
  int  i, rank, size;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0)
  {
    for(i=0;i<16;i++)
        num1[i]= (rand() % 100 + 1);
  }
  
  int *rec = malloc(sizeof(int) * 4);

  MPI_Scatter(num1,4,MPI_INT,rec,4,MPI_INT,0,MPI_COMM_WORLD);
  for(i=0;i<4;i++) {
    printf("Number from process %d is : %d\t", rank, rec[i]);
    nname(rec[i]);
    printf("\n");
  }

  MPI_Finalize();
}