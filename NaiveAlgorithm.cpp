#include <iostream>
#include <vector>
#include "NaiveAlgorithm.h"


NaiveSearch:: NaiveSearch(const std::string& input_string){
        this->input_string = preproccess(input_string);
        this->length = int(input_string.size());
        std::cout << this->input_string << std::endl;
}

std::vector<int>NaiveSearch::search(const std::string & pattern){
        std::string in = preproccess(pattern);
        std::vector<int> result;
        int i, j, l;
        l = int (pattern.size());
        for (i = 0; i < length; ++i) {
            for (j = 0; j < l; ++j) {
                printf("i:%d, j:%d, ci:%c, cj:%c\n", i, j, this->input_string[i+j], pattern[j]);
                if (this->input_string[i+j] != in[j]) break;
            }
            if (j == l) {
                result.push_back(i);
                printf("%d", i);
            }
            if (length - i < j) break;
        }
        return result;
}

std::string NaiveSearch::preproccess(const std::string & string){
        std::string out = string;
        for (int i = 0; i < string.size(); i++) out[i] = char(std::toupper(string[i]));
        return out;
}