/*
Gyeonghun Kim (Mar. 31, 2022)
Example code in PSC class
compile: g++ example4.cpp -fopenmp -o example4.out

** result: 

*/

#include <iostream>
#include <array>
#include <omp.h>

int main()
{
    const int N = 3;
    omp_set_num_threads(N);

    auto A = std::array<std::array<double, N>, N>();
    auto b = std::array<double, N>();
    auto c = std::array<double, N>();
// Initialize the matrix and vector
#pragma omp parallel for
    for (auto i = 0; i < N; ++i)
    {
        for (auto j = 0; j < N; ++j)
        {
            A[i][j] = i + j;
        }
        b[i] = i;
    }
    std::cout << "Initialized A matrix" << std::endl;
    for (auto i = 0; i < N; ++i)
    {
        for (auto j = 0; j < N; ++j)
        {
            std::cout << A[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "Initialized b vector" << std::endl;
    for (auto i = 0; i < N; ++i)
    {
        std::cout << b[i];
        if (i < (N - 1))
            std::cout << ", ";
        else
            std::cout << std::endl;
    }

    double sum = 0;
    // Matrix vector multiplication
#pragma omp parallel for private(sum)
    for (auto i = 0; i < N; ++i)
    {
        sum = 0.;
        for (auto j = 0; j < N; ++j)
        {
            sum += A[i][j] * b[j];
        }
        c[i] = sum;
    }

    std::cout << "Result c vector" << std::endl;
    for (auto i = 0; i < N; ++i)
    {
        std::cout << c[i];
        if (i < (N - 1))
            std::cout << ", ";
        else
            std::cout << std::endl;
    }
}