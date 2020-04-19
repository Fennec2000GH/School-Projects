#include "frequency_table.h"
#include <fstream>
#include <iterator>
using namespace std;

//CONSTRUCTORS
frequency_table::frequency_table(const std::string &file_name) {
    string filepath = file_name;
    ifstream input;
    input.open(filepath.c_str(), ios::in);
    if(!input.is_open()) { throw runtime_error("File not open!"); }
    char ch;
    while(input >> noskipws >> ch) {
        bool first_occurrence = frequency.try_emplace(ch, 1).second;
        if(!first_occurrence) { ++frequency[ch]; }
    }
    input.close();

}

//DESTRUCTORS
//no dynamic allocation used
frequency_table::~frequency_table() { frequency.clear(); }

//ACCESSORS
int frequency_table::get_frequency(char c) const {
    //character not present in input file
    if(frequency.count(c) == 0) { return 0; }
    return frequency.count(c) > 0 ? frequency.find(c) -> second : 0;
}

//number of unique characters encountered
int frequency_table::unique_size() const { return frequency.size(); }

unordered_set<char> frequency_table::get_characters() const {
    unordered_set<char> keys;
    for(unordered_map<char, unsigned>::const_iterator it = frequency.cbegin(); it != frequency.cend(); it++) { keys.insert(it -> first); }
    return keys;
}

//int main() { return 0; }