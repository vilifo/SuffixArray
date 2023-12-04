#include "NaiveAlgorithm.h"
#include "suffixArray.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <functional>

std::string openTextFile(std::string & filepath){
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return "";
    }
    std::string fileContent(
            (std::istreambuf_iterator<char>(inputFile)),
            std::istreambuf_iterator<char>()
    );
    inputFile.close();
    return fileContent;
}

std::vector<std::string> loadPatterns(std::string &patternsFile) {
    std::string patternsText = openTextFile(patternsFile);
    std::vector<std::string> patterns = std::vector<std::string>();
    std::istringstream inputStream(patternsText);

    std::string line;
    while (std::getline(inputStream, line)) {
        patterns.push_back(line);
    }

    return patterns;
}

void printResult(const std::vector<int>& result, const std::string &pattern, long duration){
    if (!result.empty()) {
        if (result.size() <= 5){
            std::cout << "|\tPositions of the pattern (" << pattern << ") in the text: ";
            for (int pos : result) {
                std::cout << pos << " ";
            }
        } else{
            std::cout << "|\tPattern (" << pattern << ") was found " << result.size() << " times ";
        }
        std::cout << "in " << duration << " μs."<< std::endl;
    } else {
        std::cout << "|\tPattern (" << pattern << ") was not found in the text in " << duration << " μs." << std::endl;
    }
}

void testFile(std::string & textFile, std::string & patternsFile){
    std::string text = openTextFile(textFile);
    std::vector<std::string> patterns = loadPatterns(patternsFile);
    if (text.empty() || patterns.empty()){
        std::cout << "Text or patterns are empty. Skipping" << std::endl;
        return;
    }
    std::cout << "\nTesting file: " << textFile << " vs " << patternsFile <<  std::endl;
    std::vector<int> result;

    auto start_time = std::chrono::high_resolution_clock::now();
    SuffixArray suffixArray = SuffixArray(text);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Suffix Array building: " << duration << " μs" << std::endl;

    std::cout << "Search:" <<std::endl;
    for(const auto & pattern : patterns){
        start_time = std::chrono::high_resolution_clock::now();
        result = suffixArray.search(pattern);
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        printResult(result, pattern, duration);
    }
    std::cout << "SimpleSearch:" <<std::endl;
    for(const auto & pattern : patterns){
        start_time = std::chrono::high_resolution_clock::now();
        result = suffixArray.searchSimple(pattern);
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        printResult(result, pattern, duration);
    }


    start_time = std::chrono::high_resolution_clock::now();
    NaiveSearch naiveSearch = NaiveSearch(text);
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Naive Search: " << duration << " μs" << std::endl;

    for(const auto & pattern : patterns){
        start_time = std::chrono::high_resolution_clock::now();
        result = naiveSearch.search(pattern);
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        printResult(result, pattern, duration);
    }

}

int main() {
    std::vector<std::pair<std::string, std::string>> test = {
//            {"tests/smallest.txt", "tests/smallest_patterns.txt"},
            {"tests/small.txt", "tests/small_patterns.txt"},
            {"tests/harry.txt", "tests/harry_patterns.txt"},
            {"tests/dna.txt", "tests/dna_patterns.txt"},
            {"tests/20000-Leagues-Under-the-Sea.txt", "tests/20000-Leagues-Under-the-Sea_patterns.txt"},
            {"tests/dna_large.txt", "tests/dna_large_patterns.txt"}
    };
    for (auto testItem:test) {
        testFile(testItem.first, testItem.second);
    }
    return 0;
}
