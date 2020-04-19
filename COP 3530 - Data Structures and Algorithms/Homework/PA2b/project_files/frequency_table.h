#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class frequency_table {
public:
    //CONSTRUCTORS
    frequency_table(const std::string &file_name);

    //DESTRUCTORS
    ~frequency_table();

    //ACCESSORS
    int get_frequency(char c) const;
    int unique_size() const;
    unordered_set<char> get_characters() const;

private:
    // Something to store the frequency of each character
    unordered_map<char, unsigned> frequency;

};
