#pragma once
#include "frequency_table.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
using namespace std;

// struct for the nodes of the tree?
struct Node {
    //CONSTRUCTORS
    Node(unsigned new_val);
    Node(unsigned new_val, char new_character);

    //OPERATOR OVERLOADING
    bool operator == (const Node &n) const;
    bool operator != (const Node &n) const;
    bool operator <= (const Node &n) const;
    bool operator >= (const Node &n) const;
    bool operator < (const Node &n) const;
    bool operator > (const Node &n) const;

    //MEMBER VARIABLES
    optional<char> character;
    unsigned val; //frequency for leaf, or sum of val from its children if not leaf
    unique_ptr<Node> left;
    unique_ptr<Node> right;
};

class huffman_encoder {
public:
    //CONSTRUCTORS
    huffman_encoder(const frequency_table &table);

    //DESTRUCTORS
    ~huffman_encoder();

    //ACCESSORS
    std::string get_character_code(char c) const;
    std::string encode(const std::string &file_name) const;
    std::string decode(const std::string &string_to_decode) const;
    void traversal(const unique_ptr<Node> &ptr, string code);
    void print_code() const;

private:
    //MEMBER VARIABLES
    unordered_map<char, string> code_map;
    unordered_map<string, char> code_map_inv;


};
