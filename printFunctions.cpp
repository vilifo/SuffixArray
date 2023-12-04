#include <iostream>
#include <vector>
#include "printFunctions.h"


template void printVector<int, int>(const std::vector<int>&, char);
template void printVector<int, char>(const std::vector<int>&, char);
template void printVector<bool, int>(const std::vector<bool> &, char);

template void printVector<int, char>(const std::vector<int> &);

template<typename T, typename C>
void printVector(const std::vector<T> &inVector, char sep){
    for (T a:inVector) {
        std::cout << static_cast<C>(a) << sep;
    }
    std::cout << std::endl;
}
void printStringVector(const std::vector<int> &inVector, char sep){
    for (int a:inVector) {
        std::cout << (a == 7 ? '$' : static_cast<char>(a)) << sep;
    }
    std::cout << std::endl;
}

template<typename T, typename C>
void printVector(const std::vector<T> &vector){
    for (T a:vector) {
        std::cout << static_cast<C>(a);
    }
    std::cout << std::endl;
}

