#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void aXPY(long *X, long *Y, long *Z, long alpha, int n) {
    for (int i = 0; i < n; i++) {
        Z[i] = alpha * X[i] + Y[i];
    }
}

void fill_even(long *X, int n) {
    for (int i = 0; i < n; i++) {
        X[i] = 2 * i;
    }
}

void fill_odd(long *X, int n) {
    for (int i = 0; i < n; i++) {
        X[i] = 2 * i + 1;
    }
}


int main() {
    int N = 1000000;
    int i = 0;

    clock_t start_time, end_time;
    double execution_duration;

    long alpha = 3;

    long* X;
    long* Y;
    long* Z;

    X = (long *)malloc(sizeof(long) * N);
    Y = (long *)malloc(sizeof(long) * N);
    Z = (long *)malloc(sizeof(long) * N);

    fill_even(X,N);
    fill_odd(Y,N);

    start_time = clock();

    aXPY(X, Y, Z, alpha, N);

    end_time = clock();

    execution_duration = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n\nC version took %f \n", execution_duration*1000);

    // Free allocated memory
    free(X);
    free(Y);
    free(Z);

    return 0;
}
