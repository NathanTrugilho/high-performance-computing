/*
Objetivo: Paralelizar um algoritmo simples (integração numérica)

Tarefa:
- Paralelizar o loop principal
- Garantir resultado correto (atenção a race condition)
- Usar reduction corretamente

Dica:
- Esse código tem um padrão clássico de paralelização
*/

#include <stdio.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

double integration(long long n, double a, double h){
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

int main() {
    long long num_intervals = 2000000000; 
    double inf_limit = 0.0, sup_limit = 1.0;
    double interval_width = (sup_limit - inf_limit) / num_intervals;

    printf("Approx for PI: %.30f\n", integration(num_intervals, inf_limit, interval_width));

    return 0;
}

// num_intervals = 2000000000; 
// Naive : 10 sec
// Parallel : 3.5 sec
// Parallel with 03 : 0.9 sec
//gcc -fopenmp -O3 .\integration.c; time .\a.exe