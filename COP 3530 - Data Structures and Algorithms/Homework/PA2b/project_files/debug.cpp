
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include "frequency_table.cpp"
#include "huffman_encoder.cpp"
using namespace std;

//111
//TEST_CASE("Single Letter Code Length")
//{
int main() {
    auto table = frequency_table("texts/single_letter.txt");
    huffman_encoder tree(table);
    std::string encoded_string = tree.encode("texts/single_letter.txt");

    cout << "Frequencies: " << endl;
    unordered_set<char> char_set = table.get_characters();
    for(const auto &ch : char_set) { cout << ch << ": " << table.get_frequency(ch); }
    cout << "\nx encoded = " << encoded_string << endl;
//    CHECK(encoded_string.length() == 1);
}
//}

