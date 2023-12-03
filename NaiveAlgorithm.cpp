#include <iostream>
#include <vector>
#include "NaiveAlgorithm.h"


NaiveSearch:: NaiveSearch(const std::string& string){
        this->string = preproccess(string);
        this->length = int(string.size());
#ifdef TESTING
    std::cout << this->string << std::endl;
#endif
}

std::vector<int>NaiveSearch::search(const std::string & pattern){
        std::string in = preproccess(pattern);
#ifdef TESTING
        std::cout << in << std::endl;
#endif
        std::vector<int> result;
        int i, j, l;
        l = int (pattern.size());
        for (i = 0; i < length; ++i) {
            for (j = 0; j < l; ++j) {
                if (this->string[i+j] != in[j]) break;
            }
            if (j == l) {
                result.push_back(i);
            }
            if (length - i < j) break;
        }
        return result;
}

std::string NaiveSearch::preproccess(const std::string & string){
        std::string out = string;
        for (int i = 0; i < int(string.size()); i++) out[i] = char(std::toupper(string[i]));
        return out;
}