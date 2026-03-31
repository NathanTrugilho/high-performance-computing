#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 500000000
#define BLOCK_SIZE 10000

// Soma prefixada (dependente)
void naive_prefix_sum(double *input, double *output) {
    output[0] = input[0];

    for (long long i = 1; i < N; i++) {
        output[i] = output[i - 1] + input[i];
    }
}

// Inicialização
void inicializa(double *v) {
    for (long long i = 0; i < N; i++) {
        v[i] = (double) rand() / RAND_MAX;
    }
}

// Soma simples (para validação)
double soma(double *v) {
    double s = 0.0;
    for (long long i = 0; i < N; i++) {
        s += v[i];
    }
    return s;
}

int main() {
    srand(42);

    double *input = malloc(sizeof(double) * N);
    double *output = malloc(sizeof(double) * N);

    if (!input || !output) {
        printf("Erro de alocação\n");
        return 1;
    }

    inicializa(input);

    clock_t start = clock();

    pro_prefix_sum(input, output);

    clock_t end = clock();

    double tempo = (double)(end - start) / CLOCKS_PER_SEC;

    double total_input = soma(input);
    double ultimo_prefixo = output[N - 1];

    printf("Soma total input: %.10f\n", total_input);
    printf("Ultimo valor prefixo: %.10f\n", ultimo_prefixo);
    printf("Tempo: %f segundos\n", tempo);

    free(input);
    free(output);


    // For N = 500000000
    // Naive: 1.853 sec
    // Parallel: 6 sec
    // Parallel with O3: 5 sec

    return 0;
}