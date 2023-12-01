#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <unordered_map>

#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H
const char SENTINEL = '\7'; // Defining sentinel as ASCII Bell to be smaller than any printable character

class SuffixArray {
public:
    explicit SuffixArray(const std::string &input_string);

    std::vector<int> search(const std::string &pattern);

private:
    std::string string;
    int length;
    std::vector<int> SA;
    std::vector<int> LCPArray;

    void createSuffixArray(const std::string & in_string);

    static std::vector<int> reduce(const std::vector<int> &string, std::vector<bool> &typeArray, std::vector<int> &LMSPointers,
                                   std::map<int, int>& charCount, std::map<std::vector<int>, std::pair<std::vector<int>, int>> &LMSSubstrings,
                                   bool& unique);

    static std::vector<int> trivialSuffixArray(const std::vector<int> & in_string);

    static std::vector<int> induce(const std::vector<int> &preSuffixArray, const std::vector<int> &string,
                                   const std::map<int, int> &charCount, const std::vector<int>& LMSPointers,
                                   const std::vector<bool>& typeArray);

    template<typename T>
    static std::vector<T> vectorSubRange(const std::vector<T>& originalVector, size_t start, size_t l);

    template<typename T, typename C>
    static void printVector(const std::vector<T> &vector);

    template<typename T, typename C>
    static void printVector(const std::vector<T> &vector, char sep);

    void bin_cosi(int  i, int j);

    void createLCPArray();

    int lcp(int i, int j);

    int lcp(const std::string &pattern, int i, int m);

    std::pair<int, int> simpleSearch(const std::string &pattern);

    int LCPLookup(int d, int f);

    std::pair<int, int> searchMP(const std::string &spattern);
};
#endif