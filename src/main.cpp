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
            // std::cerr << "Error: " << p << " does not exists.\n";
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

    //TODO: start csv
    std::ofstream csv;
    csv.open("results.csv");
    csv << "FILE, MERGE_SORT(ms), SUPER_MERGE(ms),\n";

    int count = 0;
    for (auto p : targets){
        std::cout << "Target: " << p << '\n';
        std::cerr << "\33[2K\rLoading file (" << ++count << '/' << targets.size() << "): " << p;

        std::ifstream in;
        in.open(p);

        std::vector<int> aux_vec;

        int aux_i;
        while (in >> aux_i)
            aux_vec.push_back(aux_i);

        auto arr = new int[aux_vec.size()];

        std::copy(aux_vec.begin(),aux_vec.end(),arr);
        
        auto t1 = std::chrono::steady_clock::now();
        paa::merge_sort(arr,0,aux_vec.size());
        auto t2 = std::chrono::steady_clock::now();
        auto span_ms = std::chrono::duration_cast<std::chrono::duration<double,std::milli>>(t2 - t1);
        std::cout << "\tmergesort: " << span_ms.count() << " ms.\n";

        std::copy(aux_vec.begin(),aux_vec.end(),arr);

        auto t3 = std::chrono::steady_clock::now();
        paa::super_merge_sort(arr,0,aux_vec.size());
        auto t4 = std::chrono::steady_clock::now();
        auto span_sm = std::chrono::duration_cast<std::chrono::duration<double,std::milli>>(t4 - t3);
        std::cout << "\tsupermerge: " << span_sm.count() << " ms.\n";

        //TODO: add to csv file
        csv << p << ',' << span_ms.count() << ',' << span_sm.count() << ",\n";

        delete[] arr;
        in.close();
    }
    std::cerr << "\33[2K\rDone.\n";

    //TODO: end csv
    csv.close();

    return 0;
}
