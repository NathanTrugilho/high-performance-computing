#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 700000000LL

int main() {
    double *a = malloc(N * sizeof(double));
    double *b = malloc(N * sizeof(double));
    double *c = malloc(N * sizeof(double));

    if (a == NULL || b == NULL || c == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    #pragma omp parallel for
    for (long long i = 0; i < N; i++) {
        b[i] = i * 0.5;
        c[i] = i * 0.2;
    }

    int max_threads = omp_get_max_theadrs();
    double *sum_batch = malloc(max_threads * sizeof(double));

    double start = omp_get_wtime();

    a[0] = b[0] + c[0];

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int thread_amount = omp_get_num_threads();

        long long chunk = N / thread_amount;
        long long subpart_init = tid * chunk;
        long long subpart_end = (tid == thread_amount - 1) ? N : subpart_init + chunk;

        if (subpart_init == 0)
            subpart_init = 1;

        for (long long i = subpart_init; i < subpart_end; i++)
            a[i] = b[i] * c[i];

        for (long long i = subpart_init + 1; i < subpart_end; i++)
            a[i] += a[i - 1];

        sum_batch[tid] = a[subpart_end - 1];

        #pragma omp barrier

        double offset = 0.0;
        for (int i = 0; i < tid; i++)
            offset += sum_batch[i];

        for (long long i = subpart_init; i < subpart_end; i++)
            a[i] += offset;
    }

    double end = omp_get_wtime();

    printf("Ultimo valor: %.2f\n", a[N - 1]);
    printf("Tempo: %f segundos\n", end - start);

    free(a);
    free(b);
    free(c);
    free(sum_batch);

    return 0;
}

//For N = 700000000, last val = 11433333308836661986066432.00 