#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

  MPI_Init (&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int vowels = 0, consonants = 0;
  char s[10], r[10];
  
  if (rank == 0) {
    
    printf("Process %d inputting string and sending it\n", rank);
    printf("Enter the string to be sent\n");
    
    scanf("%s",s);
    int l = strlen(s);
    
    MPI_Send(&s, l, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
  } 

  else if (rank == 1) {

    //memset(r, 0, 10);
    MPI_Recv(&r, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received string %s from process 0\n", rank, r);
    
    //Counting vowels
    for(int i = 0; i < strlen(r); i++) 
        if(r[i] == 'a' || r[i] == 'e' || r[i] == 'i' || r[i] == 'o' || r[i] == 'u')
            ++vowels;
  
    MPI_Send(&vowels, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
  }

  else if (rank == 2) {

    //memset(r, 0, 10);
    MPI_Recv(&r, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received string %s from process 0\n", rank, r);

    //Count consonants
    for(int i = 0; i < strlen(r); i++) 
        if(r[i] != 'a' && r[i] != 'e' && r[i] != 'i' && r[i] != 'o' && r[i] != 'u')
            ++consonants;

    MPI_Send(&consonants, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
  }

  else if (rank == 3) {

    MPI_Recv(&vowels, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received vowels count = %d from process 1\n", rank, vowels);
  }

  else if(rank == 4) {

    MPI_Recv(&consonants, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d received consonants count = %d from process 2\n", rank, consonants);

  }

  MPI_Finalize();
}