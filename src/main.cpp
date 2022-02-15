#include <iostream>
#include <chrono>

#include "paa.hpp"

int main(void) {

    int vet1[] = {9,8,7,6,5,4,3,2,1,0};
    int vet2[] = {9,8,7,6,5,4,3,2,1,0};
    
    auto t1 = std::chrono::steady_clock::now();
    paa::merge_sort(vet1, 0, 9);
    paa::super_merge_sort(vet2, 0, 9);
    auto t2 = std::chrono::steady_clock::now();

    auto span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "Took " << span.count() << " s.";
    std::cout << std::endl;

    for (int i = 0; i < 10; i++)
        std::cout << vet1[i] << ' ';
    std::cout << std::endl;

    for (int i = 0; i < 10; i++)
        std::cout << vet2[i] << ' ';
    std::cout << std::endl;

    return 0;
}