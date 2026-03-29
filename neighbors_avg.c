/*
Objetivo: Mesmo algoritmo (filtro de média), corrigindo problema de memória.
Agora usando alocação dinâmica contígua (1D) para suportar N grande.

Tarefa:
- Paralelizar os loops
- Pode usar collapse(2)
- Não precisa de reduction no filtro
- Validar com a soma final

Compile:
gcc -O2 -fopenmp filtro.c -o filtro
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20000

// Macro para indexação 2D em vetor 1D
#define IDX(i, j) ((i) * N + (j))

// Filtro de média dos vizinhos
void filtro_media(double *input, double *output) {
    #pragma omp parallel for
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            output[IDX(i,j)] = (
                input[IDX(i-1,j)] +
                input[IDX(i+1,j)] +
                input[IDX(i,j-1)] +
                input[IDX(i,j+1)] +
                input[IDX(i,j)]
            ) / 5.0;
        }
    }
}

// Inicialização
void inicializa(double *m) {
    for (long long i = 0; i < (long long)N * N; i++) {
        m[i] = (double) rand() / RAND_MAX;
    }
}

// Soma para validação
double soma_matriz(double *m) {
    double soma = 0.0;
    for (long long i = 0; i < (long long)N * N; i++) {
        soma += m[i];
    }
    return soma;
}

int main() {
    srand(28);

    double *input = malloc((long long)N * N * sizeof(double));
    double *output = malloc((long long)N * N * sizeof(double));

    if (!input || !output) {
        printf("Erro de alocação\n");
        return 1;
    }

    inicializa(input);

    filtro_media(input, output);

    double soma = soma_matriz(output);
    
    printf("Soma da matriz filtrada: %.10f\n", soma);
    
    free(input);
    free(output);
    
    return 0;
}


//Expected result: 199953615.3613343537
// For N = 20000
// Naive: 8.5 sec
// Parallel: 6 sec
// Parallel with O3: 5 sec