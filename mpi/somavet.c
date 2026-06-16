#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size); 

  int N = 1000;
  int *vet;

  if(rank == 0)
  {
    vet = malloc(N * sizeof(int));
    for(int i = 0; i < N; i++)
      vet[i] = i;
  }

  // Só funciona se N for divisível por size. O importante é pegar a ideia.
  int batch = N / size;
  int *local = malloc(batch * sizeof(int));

  MPI_Scatter(
    vet,          // vetor de origem (apenas no P0)
    batch,              // quantidade enviada para cada processo
    MPI_INT,        // tipo dos dados enviados
    local,          // onde armazenar os dados recebidos
    batch,              // quantidade recebida por processo
    MPI_INT,        // tipo dos dados recebidos
    0,              // processo raiz
    MPI_COMM_WORLD  // comunicador
  );

  int local_sum = 0;
  int global_sum = 0;

  for(int i = 0; i < batch; i++)
    local_sum += local[i];

  MPI_Reduce(
    &local_sum,    // valor que cada processo contribui
    &global_sum,    // onde o P0 armazenará o resultado
    1,              // quantidade de elementos
    MPI_INT,        // tipo dos dados
    MPI_SUM,        // operação de redução
    0,              // processo raiz
    MPI_COMM_WORLD  // comunicador
  );

  if (rank == 0)
    printf("Media: %f", (double)global_sum/N);

   MPI_Finalize();
}