#include <iostream>
#include <vector>

class NaiveSearch {
public:
    explicit NaiveSearch(const std::string& input_string){
        this->input_string = preproccess(input_string);
        this->length = int(input_string.size());
        std::cout << this->input_string << std::endl;
    }
    std::vector<int> search(const std::string & pattern){
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
private:
    std::string input_string;
    int length;

    static std::string preproccess(const std::string & string){
        std::string out = string;
        for (int i = 0; i < string.size(); i++) out[i] = char(std::toupper(string[i]));
        return out;
    }
};


int main(){
    std::string input_string;
    std::string pattern;

    std::cout << "Enter the input string: ";
    std::cin >> input_string;
    NaiveSearch NS(input_string);

    std::cout << "Enter the pattern to search for: ";
    std::cin >> pattern;
    std::vector<int> result = NS.search(pattern);

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