#include <stdio.h>
#include <cuda_runtime.h>

#define N 1024
#define THREADS 256

__global__ void reduction(int *entrada, int *saida)
{
    __shared__ int cache[THREADS];

    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    // Carrega para memória compartilhada
    cache[tid] = entrada[idx];
    __syncthreads();

    // Reduction dentro do bloco
    for (int stride = blockDim.x / 2; stride > 0; stride /= 2)
    {
        if (tid < stride)
        {
            cache[tid] += cache[tid + stride];
        }
        __syncthreads();
    }

    // Thread 0 do bloco escreve a soma parcial
    if (tid == 0)
    {
        saida[blockIdx.x] = cache[0];
    }
}

int main()
{
    int h_entrada[N];
    int h_saida[N / THREADS];

    for (int i = 0; i < N; i++)
        h_entrada[i] = 1;

    int *d_entrada, *d_saida;

    cudaMalloc(&d_entrada, N * sizeof(int));
    cudaMalloc(&d_saida, (N / THREADS) * sizeof(int));

    cudaMemcpy(d_entrada, h_entrada, N * sizeof(int), cudaMemcpyHostToDevice);

    reduction<<<N / THREADS, THREADS>>>(d_entrada, d_saida);

    cudaMemcpy(h_saida, d_saida,
               (N / THREADS) * sizeof(int),
               cudaMemcpyDeviceToHost);

    int somaFinal = 0;
    for (int i = 0; i < N / THREADS; i++)
        somaFinal += h_saida[i];

    printf("Soma = %d\n", somaFinal);

    cudaFree(d_entrada);
    cudaFree(d_saida);

    return 0;
}