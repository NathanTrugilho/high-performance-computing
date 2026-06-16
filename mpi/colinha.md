# Resumo de MPI

## Inicialização

```c
int MPI_Init(int *argc, char ***argv);
```

Inicializa o ambiente MPI. Deve ser a primeira chamada MPI do programa.

---

```c
int MPI_Finalize(void);
```

Finaliza o ambiente MPI. Deve ser a última chamada MPI.

---

```c
int MPI_Comm_rank(MPI_Comm comm, int *rank);
```

Obtém o rank (identificador) do processo atual.

---

```c
int MPI_Comm_size(MPI_Comm comm, int *size);
```

Obtém o número total de processos do comunicador.

---

# Comunicação ponto a ponto

```c
int MPI_Send(
    const void *buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm
);
```

Envia dados para outro processo.

---

```c
int MPI_Recv(
    void *buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status *status
);
```

Recebe dados de outro processo.

---

```c
int MPI_Probe(
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Status *status
);
```

Inspeciona uma mensagem antes de recebê-la.

---

```c
int MPI_Get_count(
    const MPI_Status *status,
    MPI_Datatype datatype,
    int *count
);
```

Obtém a quantidade de elementos de uma mensagem recebida.

---

# Comunicação não bloqueante

```c
int MPI_Isend(
    const void *buf,
    int count,
    MPI_Datatype datatype,
    int dest,
    int tag,
    MPI_Comm comm,
    MPI_Request *request
);
```

Inicia um envio sem bloquear o processo.

---

```c
int MPI_Irecv(
    void *buf,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm comm,
    MPI_Request *request
);
```

Inicia uma recepção sem bloquear o processo.

---

```c
int MPI_Wait(
    MPI_Request *request,
    MPI_Status *status
);
```

Espera uma operação não bloqueante terminar.

---

```c
int MPI_Waitall(
    int count,
    MPI_Request array_of_requests[],
    MPI_Status array_of_statuses[]
);
```

Espera várias operações não bloqueantes terminarem.

---

# Operações coletivas

## Broadcast

```c
int MPI_Bcast(
    void *buffer,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm comm
);
```

Um processo envia os mesmos dados para todos os processos.

---

## Reduce

```c
int MPI_Reduce(
    const void *sendbuf,
    void *recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    int root,
    MPI_Comm comm
);
```

Combina os valores de todos os processos usando uma operação e envia o resultado para o processo raiz.

Operações comuns:

```c
MPI_SUM
MPI_MAX
MPI_MIN
MPI_PROD
```

---

## AllReduce

```c
int MPI_Allreduce(
    const void *sendbuf,
    void *recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm
);
```

Igual ao Reduce, mas todos os processos recebem o resultado.

---

## Scatter

```c
int MPI_Scatter(
    const void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm
);
```

Divide um vetor do processo raiz em partes iguais e distribui entre os processos.

---

## Scatterv

```c
int MPI_Scatterv(
    const void *sendbuf,
    const int sendcounts[],
    const int displs[],
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm
);
```

Distribui quantidades diferentes de elementos para cada processo.

---

## Gather

```c
int MPI_Gather(
    const void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    int root,
    MPI_Comm comm
);
```

Coleta dados de todos os processos em um único processo raiz.

---

## AllGather

```c
int MPI_Allgather(
    const void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm
);
```

Coleta os dados de todos os processos e distribui o resultado para todos.

---

## Alltoall

```c
int MPI_Alltoall(
    const void *sendbuf,
    int sendcount,
    MPI_Datatype sendtype,
    void *recvbuf,
    int recvcount,
    MPI_Datatype recvtype,
    MPI_Comm comm
);
```

Cada processo envia dados diferentes para todos os outros processos.

---

## Barrier

```c
int MPI_Barrier(MPI_Comm comm);
```

Sincroniza os processos; nenhum continua até que todos cheguem à barreira.

---

## Scan

```c
int MPI_Scan(
    const void *sendbuf,
    void *recvbuf,
    int count,
    MPI_Datatype datatype,
    MPI_Op op,
    MPI_Comm comm
);
```

Realiza uma redução parcial acumulada (prefix sum).

---

# Tipos de dados

```c
MPI_INT
MPI_FLOAT
MPI_DOUBLE
MPI_CHAR
MPI_LONG
MPI_UNSIGNED
```

Representam os tipos básicos da linguagem C.

---

# Constantes úteis

```c
MPI_COMM_WORLD
```

Comunicador contendo todos os processos.

---

```c
MPI_ANY_SOURCE
```

Aceita mensagens de qualquer processo.

---

```c
MPI_ANY_TAG
```

Aceita mensagens com qualquer tag.

---

```c
MPI_STATUS_IGNORE
```

Ignora as informações de status em um `MPI_Recv`.

---

# Funções mais usadas

```text
MPI_Init
MPI_Finalize
MPI_Comm_rank
MPI_Comm_size
MPI_Send
MPI_Recv
MPI_Bcast
MPI_Reduce
MPI_Scatter
MPI_Scatterv
MPI_Gather
MPI_Allreduce
MPI_Barrier
```