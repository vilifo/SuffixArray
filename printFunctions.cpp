#include <iostream>
#include <vector>
#include "printFunctions.h"

template<typename T, typename C>
void printVector(const std::vector<T> &inVector, char sep){
    for (T a:inVector) {
        std::cout << a << sep;
    }
    std::cout << std::endl;
}
void printStringVector(const std::vector<int> &inVector, char sep){
    for (int a:inVector) {
        std::cout << (a == SENTINEL ? '$' : static_cast<char>(a)) << sep;
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
