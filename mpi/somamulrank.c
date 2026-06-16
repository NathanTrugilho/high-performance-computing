#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  int rank, size;
  int num = 2;
  int soma = 0;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size); 

  MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

  num*=rank;     
  
  MPI_Reduce(
    &num,
    &soma,
    1,
    MPI_INT,
    MPI_SUM,
    0,
    MPI_COMM_WORLD
  );

  if (rank == 0)
  {
    printf("Result: %d", soma);
  }

  MPI_Finalize();
}