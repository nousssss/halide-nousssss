#include "Halide.h"
#include <chrono>
#include <vector>

int main(int argc, char **argv) {

    const int N = 100'000'000;
    const int alpha = 3;

    Halide::Var i;

    // Fill two Halide buffers with first N even/odd numbers;
    Halide::Func fill_even, fill_odd;
    fill_even(i) = Halide::cast<int64_t>(2 * i);
    fill_odd(i) = Halide::cast<int64_t>(2 * i + 1);

    Halide::Buffer<int64_t> X = fill_even.realize({N});
    Halide::Buffer<int64_t> Y = fill_odd.realize({N});

    Halide::Func sum;
    // define the AXPY function as alpha * X + Y
    sum(i) = alpha * X(i) + Y(i);

    Halide::Var i_outer, i_inner;

    // Instruct Halide to split the work into 16 chunks
    // and parallelize computation on these chunks.
    // The i_outer will very from 0 to 15,
    // the i_inner will vary from 0 to N / 16 for each i_outer.
    // There also possiblity of vectorization but I could not explore it.
    
    sum.split(i, i_outer, i_inner, N / 16);
    sum.parallel(i_outer);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Halide::Buffer<int64_t> output = sum.realize({N});
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Halide version took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;

    // Verify if the halide implementation is correct with native c++;
    int64_t *X, *Y, *Z;
    X = (int64_t *)malloc(sizeof(int64_t) * N);
    Y = (int64_t *)malloc(sizeof(int64_t) * N);

    for (int i = 0; i < N; i++) {
        X[i] = (2 * i);
        Y[i] = (2 * i + 1);
    }

    for (int i = 0; i < N; i++) {
        if (output(i) != (alpha * X[i] + Y[i])) {
            return -1;
        }
    }
    std::cout << "Halide matches native C++ implementation." << '\n';
    return 0;
}