/*
Gyeonghun Kim (Mar. 31, 2022)
Example code in PSC class
compile: g++ example5.cpp -fopenmp -o example5.out

** result: 

*/

#include <iostream>
#include <array>
#include <cmath>
#include <omp.h>

const int N = 3;

auto JacobiMethod(std::array<std::array<double, N>, N> A, std::array<double, N> b, std::array<double, N> x0, double TOL = 1e-6)
{
    std::array<double, N> x{
        0.,
    };
    std::array<double, N> x_old(x0);
    double error = TOL + 1;
    int max_iter = 100;
    double sum = 0;
    for (auto iter = 0; iter < max_iter; ++iter)
    {
        // Calculate Jacobi iteration
#pragma omp parallel for shared(A, b, x_old, x) private(sum)
        for (auto i = 0; i < N; ++i)
        {
            sum = 0;
            for (auto j = 0; j < N; ++j)
            {
                if (i != j)
                    sum += A[i][j] * x_old[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }

        error = 0;
#pragma omp parallel for shared(x_old, x) reduction(+ \
                                                    : error)
        for (auto i = 0; i < N; ++i)
        {
            error += std::pow(x[i] - x_old[i], 2);
        }
        error = std::sqrt(error);

        std::cout << "Error in iteration " << iter << ": " << error << std::endl;
        if (error < TOL)
            break;
        x_old = x;
    }

    return x_old;
}

auto MatrixVectorMultiplication(std::array<std::array<double, N>, N> A, std::array<double, N> b)
{
    double sum = 0;
    auto c = std::array<double, N>{
        0,
    };
#pragma omp parallel for firstprivate(sum)
    for (auto i = 0; i < N; ++i)
    {
        for (auto j = 0; j < N; ++j)
        {
            sum += A[i][j] * b[j];
        }
        c[i] = sum;
    }
    return c;
}
int main()
{
    omp_set_num_threads(N);
    // Initialize Matrix A and vector x
    auto A = std::array<std::array<double, N>, N>{
        std::array<double, N>{6, 1, -2},
        std::array<double, N>{4, 7, -2},
        std::array<double, N>{1, -1, 3}};
    auto b = std::array<double, N>{3, 0, 3};
    auto x0 = std::array<double, N>{1, 1, 1};
    auto x = JacobiMethod(A, b, x0, 1e-10);
    for (auto one_x : x)
    {
        std::cout << one_x << ", ";
    }
    std::cout << std::endl;
    std::cout << "check" << std::endl;
    auto b_check = MatrixVectorMultiplication(A, x);
    for (auto i = 0; i < N; ++i)
    {
        std::cout << b[i] << " -- " << b_check[i] << std::endl;
    }
}
