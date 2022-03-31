/*
Gyeonghun Kim (Mar. 13, 2022)
Example code in PSC class
compile: g++ example1.cpp -fopenmp -o example1.out

** result: 
    4threads set by me
    128 procs
    4 max. threads
    1 thread now
    Fork!
    Hello, I'm thread 0
    0 / 4 = 0
    Hello, I'm thread 3
    3 / 4 = 0.75
    Hello, I'm thread 1
    1 / 4 = 0.25
    Hello, I'm thread 2
    2 / 4 = 0.5
    Join!

** result without critical:
    4threads set by me
    128 procs
    4 max. threads
    1 thread now
    Fork!
    Hello, I'm thread 0
    Hello, I'm thread Hello, I'm thread 3
    3 / 4 = 1
    1 / 4 = Hello, I'm thread 20 / 4 = 0.75
    0

    2 / 4 = 0.25
    0.5
    Join!

** result with omp_get_num_threads() inside:
    4threads set by me
    128 procs
    4 max. threads
    1 thread now
    Fork!
    4 thread now
    Hello, I'm thread 0
    0 / 4 = 0
    4 thread now
    Hello, I'm thread 3
    3 / 4 = 0.75
    4 thread now
    Hello, I'm thread 2
    2 / 4 = 0.5
    4 thread now
    Hello, I'm thread 1
    1 / 4 = 0.25
    Join!
*/

#include <iostream>
#include <omp.h>

int main()
{
    int id, N;
    float fraction;

    N = 4;
    std::cout << N << "threads set by me" << std::endl;
    omp_set_num_threads(N);
    std::cout << omp_get_num_procs() << " procs" << std::endl;
    std::cout << omp_get_max_threads() << " max. threads" << std::endl;
    std::cout << omp_get_num_threads() << " thread now" << std::endl;
    std::cout << "Fork!" << std::endl;
#pragma omp parallel private(id, fraction) shared(N)
    {

        id = omp_get_thread_num();
        fraction = (float)id / (float)N;

#pragma omp critical(printing)
        {
            // std::cout << omp_get_num_threads() << " thread now" << std::endl;
            std::cout << "Hello, I'm thread " << id << std::endl;
            std::cout << id << " / " << N << " = " << fraction << std::endl;
        }
    }
    std::cout << "Join!" << std::endl;
}
