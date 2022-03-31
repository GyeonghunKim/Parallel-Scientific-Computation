/*
Gyeonghun Kim (Mar. 13, 2022)
Example code for PSC class
compile: g++ reduction_clause.cpp -fopenmp -o reduction_clause.out

** result: 
    0
    1
    2
    3
    4
    sum: 21881
    mul: 68969472
*/

#include <iostream>
#include <vector>
#include <omp.h>

int main()
{
    int i, N = 5, sum = 0, mul = 1;

    omp_set_num_threads(N);

#pragma omp parallel reduction(+                  \
                               : sum) reduction(* \
                                                : mul) private(i)
    {
        i = omp_get_thread_num();
        sum = sum + (i + 1);
        mul = mul * (i + 1);

#pragma omp critical(printing)
        {
            std::cout << i + 1 << std::endl;
        }
    }

    std::cout << "sum: " << sum << std::endl;
    std::cout << "mul: " << mul << std::endl;
    return 0;
}
