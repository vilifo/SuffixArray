#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>

const char SENTINEL = '\7'; // Defining sentinel as ASCII Bell to be smaller than any printable character

class SuffixArray {
public:
    explicit SuffixArray(const std::string& input_string) {
        string = std::string(input_string);
        length = int(string.size());
        SA = std::vector<int>(length);
        for(auto &s: string){ // Case-insensitive approach
            s = char(toupper(s));
        }
        createSuffixArray(string);
        createLCPArray();
#ifdef DEBUG
//        printf("\t");
        for (int i = 0; i < length; ++i) {
            printf("\t%d", i);
        }
        printf("\nS:");
        for (auto c: this->string) {
            printf("\t%c", c);
        }
        printf("\nSA:\t");
        printVector<int, int>(SA, '\t');
        printf("LCP:\t");
        printVector<int, int>(LCPArray, '\t');
#endif
    }

    std::vector<int> search(const std::string& pattern) {
        // Search for the pattern in the suffix array
        std::string spattern = std::string (pattern);
        for(auto &s: spattern){ // Case-insensitive approach
            s = char(toupper(s));
        }
        std::vector<int> r = std::vector<int>();
        std::pair<int, int> r1 = searchMP(spattern);
        if (r1.second == -1) r.push_back(r1.first);
        return r;
    }

private:
    std::string string;
    int length;
    std::vector<int> SA;
    std::vector<int> LCPArray;

    void createSuffixArray(const std::string & in_string){
        std::vector<std::vector<bool>> typeArrays;
        std::vector<std::vector<int>> LMSPointersArray;
        std::vector<std::map<int, int>> charCounts;
        std::vector<std::map<std::vector<int>, std::pair<std::vector<int>, int>>> LMSSubstringArray;
        std::vector<std::vector<int>> suffixArrays;
        std::vector<std::vector<int>> strings;

        size_t n = size_t(std::log2(std::log2(in_string.size()))) + 2;
        typeArrays = std::vector<std::vector<bool>>(n);
        LMSPointersArray = std::vector<std::vector<int>>(n);
        charCounts = std::vector<std::map<int, int>>(n);
        LMSSubstringArray =
                std::vector<std::map<std::vector<int>, std::pair<std::vector<int>, int>>>(n);
        suffixArrays = std::vector<std::vector<int>>(n);
        strings = std::vector<std::vector<int>>(n);

        std::vector<int> int_string = std::vector<int>(in_string.size() + 1);
        for (size_t i=0; i < in_string.length(); i++) {
            int_string[i] = static_cast<int>(static_cast<unsigned char >(in_string[i]));
        }
        int_string[int_string.size()-1] = SENTINEL;

        bool unique = false;
        int index = 0;
        strings[index] = int_string;
        while (! unique){ // Reducing
            strings[index+1] = reduce(strings[index], typeArrays[index],
                                            LMSPointersArray[index],charCounts[index],
                                            LMSSubstringArray[index], unique);
            index++;
        }
        suffixArrays[index] = trivialSuffixArray(strings[index]);
        index--;
        for (; index > -1; index--) { // Inducing
            suffixArrays[index] = induce(suffixArrays[index+1], strings[index],
                                               charCounts[index], LMSPointersArray[index],
                                               typeArrays[index]);
        }
        for (int i = 0; i < this->length; ++i) this->SA[i] = suffixArrays[0][i + 1];
    }

    static std::vector<int> reduce(const std::vector<int> &string, std::vector<bool> &typeArray, std::vector<int> &LMSPointers,
                std::map<int, int>& charCount, std::map<std::vector<int>, std::pair<std::vector<int>, int>> &LMSSubstrings,
                bool& unique){

        int n = int(string.size());
        typeArray = std::vector<bool>(n);
        LMSPointers = std::vector<int>();
        typeArray[n - 1] = true;
        charCount[string[n - 1]]++;
        LMSPointers.push_back(n-1);

        // Iterate over the input string in order to construct type array, pointer array and LMS substring array
        for(int i = int(n-2); i>=0; i--){
            charCount[string[i]]++; // Counting characters occurrence for sorting later

            if((string[i] < string[i+1]) ||
               (string[i] == string[i+1] && typeArray[i + 1])){
                typeArray[i] = true; // S-type
            } else{
                typeArray[i] = false; // L-type
                if (typeArray[i + 1]){ // If the previous symbol was S-type, then it's leftmost one
                    std::vector<int> s = vectorSubRange(string, i+1, LMSPointers[0] - i - 1);
                    LMSSubstrings[s].first.insert(LMSSubstrings[s].first.begin(), i + 1);
                    LMSPointers.insert(LMSPointers.begin(), i + 1);
                }
            }
        }

        if(typeArray[0]){ // This case wasn't considered in the loop
            std::vector<int> s = vectorSubRange(string, 0, LMSPointers[0] + 1);
            LMSSubstrings[s].first.insert(LMSSubstrings[s].first.begin(), 0);
            LMSPointers.insert(LMSPointers.begin(), 0);
        }

        int index = 0;
        unique = true;
        for(auto &item : LMSSubstrings){ // Assigning character to substring according to their order
            if(item.second.first.size() > 1) unique = false;
            item.second.second = 65 + index; // Used to pretty DEBUG output
            index++;
        }
        std::vector<int> newString;
        for(unsigned int i = 0; i<LMSPointers.size()-1; i++){ // Building string for next reduction
            auto str = vectorSubRange(string, LMSPointers[i], LMSPointers[i+1] - LMSPointers[i]);
            newString.push_back(LMSSubstrings[str].second);
        }

#ifdef DEBUG
        printf("Index :\t");
        for(int i=0; i<n; i++){
            printf("%d\t", i);
        }
        printf("\nString:\t");
        printVector<int, char>(string, '\t');
        printf("Type_A:\t");
        printVector<bool, int>(typeArray, '\t');
        printf("\nPointers:");
        for(int i: LMSPointers){
            printf("%d ", i);
        }
        printf("\nChar Counts: ");
        for (const auto& pair : charCount) {
            if (pair.first == SENTINEL) printf("$");
            std::cout << static_cast<char>(pair.first) << ": " << pair.second << " ";
        }
        printf("\nLMS Substrings: ");
        std::vector<int> s;
        for (const auto& pair : LMSSubstrings) {
            s = pair.first;
            printVector<int, char>(s);
            std::cout << "{";
            for(int i:pair.second.first){
                std::cout << i << " ";
            }
            std::cout << "}(" << static_cast<char>(pair.second.second) << "), ";
        }
        printf("\nnewString:");
        printVector<int, char>(newString);
#endif
        return newString;
    }

    static std::vector<int> trivialSuffixArray(const std::vector<int> & in_string){
        std::map<int, int> map;
        int n = int(in_string.size());
        for (int i = 0; i < n; i++) {
            map[in_string[i]] = i;
        }
        std::vector<int> suffix_array = std::vector<int>(n);
        int index = 0;
        for (auto & item:map){
            suffix_array[index] = item.second;
            index++;
        }

#ifdef DEBUG
        printf("SuffixArray:");
        for(auto & item:suffix_array) {
            printf(" %d", item);
        }
        printf("\n");
#endif
        return suffix_array;
    }

    static std::vector<int> induce(const std::vector<int> &preSuffixArray, const std::vector<int> &string,
                            const std::map<int, int> &charCount, const std::vector<int>& LMSPointers,
                            const std::vector<bool>& typeArray){
        size_t n = string.size();
        std::vector<int> suffixArray = std::vector<int>(n, -1);

        std::unordered_map<int, std::pair<int, int>> charBucketPositions;
        std::unordered_map<int, int> charTails;
        unsigned int index = 0;
        for (auto item:charCount) {
            charBucketPositions[item.first] = {index, index+item.second-1};
            charTails[item.first] = int(index+item.second-1);
            index += item.second;
        }
        for (auto it=preSuffixArray.rbegin(); it != preSuffixArray.rend(); ++it){
            // Step 1.: R->T, put items from SA1 to SA0, no change in order
            suffixArray[charTails[string[LMSPointers[*it]]]] = LMSPointers[*it];
            charTails[string[LMSPointers[*it]]]--;
        }
        int a;
        for(unsigned int i = 0; i < suffixArray.size(); i++){ // Step 2.: L->R, L-type suffixes to the head
            a = suffixArray[i]-1;
            if(a > -1 && ! typeArray[a]){
                suffixArray[charBucketPositions[string[a]].first] = a;
                charBucketPositions[string[a]].first++;
            }
        }
        for(int i = int(suffixArray.size() - 1); i > -1; i--){ // Step 3.: R->L, S-type suffixes to the tail
            a = suffixArray[i]-1;
            if(a > -1 && typeArray[a]){
                suffixArray[charBucketPositions[string[a]].second] = a;
                charBucketPositions[string[a]].second--;
            }
        }
#ifdef DEBUG
        printf("New SA:");
        printVector<int, int>(suffixArray, ' ');
#endif

        return suffixArray;
    }

    template<typename T>
    static std::vector<T> vectorSubRange(const std::vector<T>& originalVector, size_t start, size_t l) {
        // Validate start and length to ensure they are within bounds
        if (start >= originalVector.size()) {
            throw std::out_of_range("Start index is out of range");
        }

        size_t end = start + l;
        if (end > originalVector.size()) {
            throw std::out_of_range("End index is out of range");
        }

        // Create a new vector using iterators
        return std::vector<T>(originalVector.begin() + start, originalVector.begin() + end);
    }

#ifdef DEBUG
    template<typename T, typename C>
    static void printVector(const std::vector<T> &vector, char sep){
        for (T a:vector) {
            std::cout << (a == SENTINEL ? '$' : static_cast<C>(a)) << sep;
        }
        std::cout << std::endl;
    }
    template<typename T, typename C>
    static void printVector(const std::vector<T> &vector){
        for (T a:vector) {
            std::cout << (a == SENTINEL ? '$' : static_cast<C>(a));
        }
        std::cout << std::endl;
    }
#endif
    void bin_cosi(int  i, int j){ // odrekurzit?
        printf("i:%d, j:%d\n", i, j);
        if (i + 1 == j) return;
        if (i < 0 || j < 0 || j >= 2*length || i >= 2*length) return;
        int k = (i+j)/2;
        LCPArray[length + 1 + k] = lcp(i, j);
        bin_cosi(i, k);
        bin_cosi(k, j);
    }
    void createLCPArray(){
        int n = int(this->SA.size());
        this->LCPArray = std::vector<int>(2 * n);
        this->LCPArray[0] = 0;
        for (int i = 1; i < n; ++i) { // normal array
            this->LCPArray[i] = lcp(this->SA[i], this->SA[i - 1]);
        }
        bin_cosi(0, length-1);
#ifdef DEBUG
        printf("LCP: ");
        printVector<int, int>(LCPArray, ' ');
#endif
    }

    int lcp(int i, int j){
       int n = int(std::min(this->string.size()-i, this->string.size()-j));
        for (int k = 0; k < n; ++k) {
            if (this->string[i++] != this->string[j++]) return k;
        }
        return n;
    }
    int lcp(const std::string &pattern, int i, int m){
        //printf("%s vs %s", pattern.c_str(), this->string.substr(i, this->length-i).c_str());
        int j = std::min(m, this->length - i);
        for (int k = 0; k < j; ++k) {
            if (this->string[i++] != pattern[k]) return k;
        }
        return j;
    }

    std::pair<int, int> simpleSearch(const std::string &pattern){
        int m = int(pattern.size()), n = this->length;
        int d = 0, f = n, i, l;
        std::vector<int> results = std::vector<int>();

        while (d+1 < f){
            i = (d + f) / 2;
            l = lcp(pattern, this->SA[i], m);
            if (l == m and l == (n - this->SA[i])) {
                return {this->SA[i], -1};
            } else if ( l == (n - this->SA[i] - 1) ||
                        ( l != m && this->string[this->SA[i] + l] < pattern[l])){
                d = i;
            } else{
                f = i;
            }
#ifdef DEBUG
            printf("d: %d, f: %d, i: %d, l: %d\n", d, f, i, l);
#endif
        }
        return {d, f};
    }
    int LCPLookup(int d, int f){
        if (d+1 == f) return this->LCPArray[f];
        return LCPArray[this->length + 1 + (d+f)/2];
    }
    std::pair<int, int> searchMP(const std::string &spattern){
        int d=0, f= this->length, ld=0, lf=0, i, l, m = int(spattern.size());
        while (d+1 < f){
            i = (d + f) / 2;
            if (ld <= LCPLookup(SA[i], SA[f]) && LCPLookup(SA[i], SA[f]) < lf){ // case A
                d = i;
                ld = lcp(i, f);
            } else if (ld <= lf && lf < LCPLookup(SA[i], SA[f])){ // case B
                f = i;
            } else if (lf <= LCPLookup(SA[d], SA[i]) && LCPLookup(SA[d], SA[i]) < ld){ // case A for ld > lf
                f = i;
                lf = lcp(d, i);
            } else if ( lf <= ld && ld < LCPLookup(SA[d], SA[i])){ // case B for ld > lf
                d = i;
            } else{
                l = std::max(ld, lf);
                l = l + 1; // něco
                if (l == m && l == (this->SA[i])) {return {i, -1};
                } else if ((l == (this->length - this->SA[i])) ||
                           (l != m && this->string[this->SA[i] + l] < spattern[l])){
                    d = i;
                    ld = l;
                } else {
                    f = i;
                    lf = l;
                }
            }
        }
        return {d, f};
    }
};

int main() {
    //THIS IS AN EXAMPLE OF MAIN, PLEASE PREPARE YOUR OWN MAIN FOR TESTING AND EXPERIMENTS
    std::string input_string;
//    std::cout << "Enter the input string: ";
//    std::cin >> input_string;
    input_string = std::string("mmiissiissiippii");
//    input_string = std::string("mmiissiippii");
//    input_string = std::string("zemetreseni");
//    input_string = "a";
//    input_string = std::string("Lorem ipsum dolor sit amet");
    SuffixArray suffixArray(input_string);

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