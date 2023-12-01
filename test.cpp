#include "NaiveAlgorithm.h"
#include "suffixArray.h"
#include <iostream>
#include <vector>
#include <chrono>

int main() {
    //THIS IS AN EXAMPLE OF MAIN, PLEASE PREPARE YOUR OWN MAIN FOR TESTING AND EXPERIMENTS
    std::string input_string;
    std::vector<std::string> patterns;
//    std::cout << "Enter the input string: ";
//    std::cin >> input_string;
    input_string = std::string("mmiissiissiippii");
//    input_string = std::string("mmiissiippii");
//    input_string = std::string("zemetreseni");
//    input_string = "a";
//    input_string = std::string("Lorem ipsum dolor sit amet");
    auto start_time = std::chrono::high_resolution_clock::now();
    SuffixArray suffixArray(input_string);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "SA creation taken: " << duration << " microseconds" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    NaiveSearch naiveSearch = NaiveSearch(input_string);
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Naive creation taken: " << duration << " microseconds" << std::endl;

    std::string pattern;
//    std::cout << "Enter the pattern to search for: ";
//    std::cin >> pattern;
    pattern = "ssii";

    std::vector<int> result = suffixArray.search(pattern);

    if (!result.empty()) {
        std::cout << "Positions of the pattern in the text: ";
        for (int pos : result) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Pattern was not found in the text." << std::endl;
    }

    return 0;
}
