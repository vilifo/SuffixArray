#include <vector>
#include <iostream>
#ifndef NAIVESEARCH_H
#define NAIVESEARCH_H

class NaiveSearch {
public:
    explicit NaiveSearch(const std::string& input_string);
	
	std::vector<int> search(const std::string & pattern);

private:
    std::string input_string;
    int length;

    static std::string preproccess(const std::string & string);
};
#endif