/*
Gyeonghun Kim (Mar. 31, 2022)
Example code in PSC class
compile: g++ example3.cpp -fopenmp -o example3.out

** result: 
    Thread: 0
    Thread: 1
    Thread: 2
    Thread: 9
    Thread: 8
    Thread: 6
    Thread: 3
    Thread: 4
    Thread: 7
    Thread: 5

*/

#include <iostream>
#include <omp.h>

int main()
{
    int id, N = 10;
    omp_set_num_threads(N);

#pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
#pragma omp master
#pragma omp critical(printing)
        {
            std::cout << "Thread: " << id << std::endl;
        }
#pragma omp barrier
        if (id != 0)
        {
#pragma omp critical(printing)
            {
                std::cout << "Thread: " << id << std::endl;
            }
        }
    }
}