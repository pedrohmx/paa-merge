#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <filesystem>

#include "paa.hpp"

namespace fs = std::filesystem;

auto main(int argc, char *argv[]) -> int {
    std::vector<std::string> args(argv+1, argc + argv);
    std::vector<fs::path> targets;

    for (fs::path p : args) {
        if (!fs::exists(p)) {
            std::cerr << "Error: " << p << " does not exists.\n";
            continue;
        } else if (fs::is_regular_file(p)) {
            targets.push_back(p);
        } else if (fs::is_directory(p)){
            for (auto const& dir_entry : fs::directory_iterator{p}) {
                if ( (dir_entry.is_regular_file()) && (dir_entry.path().extension() == ".txt") ){
                    targets.push_back(dir_entry);
                }
            }
        }
    }

    for (auto p : targets){
        std::cout << "Target: " << p << '\n';
        std::cerr << "Loading file.\n";

        std::ifstream in;
        in.open(p);

        std::vector<int> aux_vec;

        int aux_i;
        while (in >> aux_i)
            aux_vec.push_back(aux_i);

        std::cerr << "Allocating memory\n";
        auto arr = new int[aux_vec.size()];

        std::cerr << "Copying memory for mergesort.\n";
        std::copy(aux_vec.begin(),aux_vec.end(),arr);
        
        std::cerr << "Starting mergesort\n";
        auto t1 = std::chrono::steady_clock::now();
        paa::merge_sort(arr,0,aux_vec.size());
        auto t2 = std::chrono::steady_clock::now();
        auto span = std::chrono::duration_cast<std::chrono::duration<double,std::milli>>(t2 - t1);
        std::cout << "\tmergesort: " << span.count() << " ms.\n";

        std::cerr << "Copying memory for supermerge.\n";
        std::copy(aux_vec.begin(),aux_vec.end(),arr);

        std::cerr << "Starting supermerge\n";
        t1 = std::chrono::steady_clock::now();
        paa::merge_sort(arr,0,aux_vec.size());
        t2 = std::chrono::steady_clock::now();
        span = std::chrono::duration_cast<std::chrono::duration<double,std::milli>>(t2 - t1);
        std::cout << "\tsupermerge: " << span.count() << " ms.\n";

        delete[] arr;
        in.close();
    }

    return 0;
}
