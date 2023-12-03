#include <iostream>
#include <vector>

#ifndef NI_EVY_PRINTFUNCTIONS_H
#define NI_EVY_PRINTFUNCTIONS_H

#endif //NI_EVY_PRINTFUNCTIONS_H

const char SENTINEL = '\7'; // Defining sentinel as ASCII Bell to be smaller than any printable character

template<typename T, typename C>
static void printVector(const std::vector<T> &vector);

template<typename T, typename C>
static void printVector(const std::vector<T> &vector, char sep);

static void printStringVector(const std::vector<long int> & string, char sep);