
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include "frequency_table.cpp"
#include "huffman_encoder.cpp"
using namespace std;

/*
TEST_CASE("heapify") {
//int main() {
    //test vector in pair mode
    vector <pair<char, unsigned>> freq = {{'a', 12},
                                          {'b', 16},
                                          {'c', 4},
                                          {'d', 6},
                                          {'e', 8},
                                          {'f', 20},
                                          {'g', 18}};

    //test vector in unique_ptr mode
    vector <unique_ptr<Node>> min_heap;
    transform(freq.cbegin(), freq.cend(), back_inserter(min_heap),
              [&min_heap](const pair<char, unsigned> &p) { return make_unique<Node>(p.second, p.first); } );
    for(const auto &n : min_heap) { cout << "(" << (n -> character).value() << ", " << n -> val << "), "; }
    cout << endl;
    heapify(min_heap, 0);
    for(const auto &n : min_heap) { cout << "(" << (n -> character).value() << ", " << n -> val << "), "; }
    cout << endl;

    //min_heap after heapifying the root and converted to pairs
    vector<pair<char, unsigned>> min_heap_pair;
    transform(min_heap.cbegin(), min_heap.cend(), back_inserter(min_heap_pair), [&min_heap_pair] (const auto &ptr) {
        return pair<char, unsigned>((ptr -> character).value(), ptr -> val); } );

    //expected vector after heafiying the root in pair mode
    vector <pair<char, unsigned>> expected = {{'c', 4},
                                              {'b', 16},
                                              {'a', 12},
                                              {'d', 16},
                                              {'e', 8},
                                              {'f', 20},
                                              {'g', 18}};
    CHECK(equal(expected.cbegin(), expected.cend(), min_heap_pair.cbegin()));
//    return 0;
//}
}
TEST_CASE("build heap") {
//int main() {
    vector <pair<char, unsigned>> freq = {{'a', 12},
                                          {'b', 16},
                                          {'c', 4},
                                          {'d', 6},
                                          {'e', 8},
                                          {'f', 20},
                                          {'g', 18}};

    //test vector in unique_ptr mode
    vector <unique_ptr<Node>> min_heap;
    transform(freq.cbegin(), freq.cend(), back_inserter(min_heap),
              [&min_heap, &freq](const pair<char, unsigned> &p) { return make_unique<Node>(p.second, p.first); });
    for (const auto &n : min_heap) { cout << "(" << (n->character).value() << ", " << n->val << "), "; }
    cout << endl;

    //min_heap after converting vector into actually having minimum heap property
    build_heap(min_heap);
    for (const auto &n : min_heap) { cout << "(" << (n->character).value() << ", " << n->val << "), "; }
    cout << endl;

    //min_heap after building heapand converted to pairs
    vector<pair<char, unsigned>> min_heap_pair;
    transform(min_heap.cbegin(), min_heap.cend(), back_inserter(min_heap_pair), [&min_heap_pair] (const auto &ptr) {
        return pair<char, unsigned>((ptr -> character).value(), ptr -> val); } );

    //expected vector after building heap in pair mode
    vector <pair<char, unsigned>> expected = {{'c', 4},
                                              {'d', 6},
                                              {'a', 12},
                                              {'b', 16},
                                              {'e', 8},
                                              {'f', 20},
                                              {'g', 18}};

    CHECK(equal(expected.cbegin(), expected.cend(), min_heap_pair.cbegin()));
//    return 0;
//}
}
*/

//definition for traversal (slightly edited)
/**********************************************************************************************************************/
/*
    void traversal(const unique_ptr<Node> &ptr, string code, unordered_map<char, string> &map) {
    //edge case: nullptr node
    if(ptr == nullptr) { return; }

    if(ptr -> left != nullptr) {
        traversal(ptr -> left, code += "0", map);
        code.erase(code.size() - 1, 1);
    }
    cout << (ptr -> val) << endl;
    if(ptr -> right != nullptr) {
        traversal(ptr -> right, code += "1", map);
        code.erase(code.size() - 1, 1);
    }
    if((ptr -> character).has_value()) { map.insert_or_assign((ptr -> character).value(), code); }
}
*/

/**********************************************************************************************************************/

//TEST_CAST("debugging huffman_encoder constructor") {
/*
int main() {
    //generating text file that match test vector characters
    string file = "letters.txt";
    ofstream out(file.c_str(), ios::out);
    if (!out.is_open()) { throw runtime_error("File not open!"); }

    //test vector in pair mode
    vector <pair<char, unsigned>> freq = {{'A', 15},
                                          {'B', 7},
                                          {'C', 6},
                                          {'D', 6},
                                          {'E', 5},
    };
    for (const auto &p : freq)
        for (int i = 0; i < p.second; i++) { out << p.first; }
    out.close();

    //creating frequency_table object from based on test vector frequencies
    ifstream in(file.c_str(), ios::in);
    string s;
    char ch;
    while (in.get(ch)) { s += ch; }
    cout << "Contents of letters.txt: " << s << endl << endl;

    frequency_table ft(file);
    cout << "Frequency:" << endl;
    for (const auto &p : freq) { cout << p.first << ": " << ft.get_frequency((char) p.first) << endl; }
    cout << endl;
*/

//definition of huffman_encoder constructor
/**********************************************************************************************************************/
    /*
    unordered_set<char> char_set = ft.get_characters();
    vector <unique_ptr<Node>> min_heap;

    //filtering character set only for non-zero frequency characters and then storing them inside a vector
    for (char ch : char_set) { if (ft.get_frequency(ch) == 0) { char_set.erase(ch); }}
    transform(char_set.cbegin(), char_set.cend(), back_inserter(min_heap),
              [&ft, &char_set](char ch) { return make_unique<Node>(ft.get_frequency(ch), ch); });

    //delete
    cout << "Before building min_heap..." << endl;
    for (const auto &n : min_heap) { cout << "(" << (n->character).value() << ", " << n->val << "), "; }
    cout << endl;

    //building min heap
    build_heap(min_heap);

    //delete
    cout << "After building min_heap..." << endl;
    for (const auto &n : min_heap) { cout << "(" << (n->character).value() << ", " << n->val << "), "; }
    cout << endl << endl;


    //building Huffman tree
    unique_ptr <Node> combined = nullptr;
    while (min_heap.size() > 2) {
        //left child of root is smaller than right child
        if (*min_heap[1] <= *min_heap[2]) {
            //creating new node with children being the two smallest nodes in min heap
            combined = make_unique<Node>(min_heap[0]->val + min_heap[1]->val);
            combined->left = move(min_heap[0]);
            combined->right = move(min_heap[1]);

            //delete
            cout << combined->val << endl;

            min_heap.front() = move(combined); //make former root the combined node

            //delete
            print_vector(min_heap);
            cout << "checkpoint 1.1" << endl;

            swap(min_heap, 1, min_heap.size() - 1); //swap former left child with last node
            min_heap.erase(prev(min_heap.end())); //erase last node after being moved

            //heapify left sub-heap
            heapify(min_heap, 1);

            //delete
            print_vector(min_heap);
            cout << "checkpoint 1.2" << endl;

        } else { //right child of root is smaller than left child
            //creating new node with children being the two smallest nodes in min heap
            combined = make_unique<Node>(min_heap[0]->val + min_heap[2]->val);
            combined->left = move(min_heap[0]);
            combined->right = move(min_heap[2]);

            //delete
            cout << combined->val << endl;

            min_heap.front() = move(combined); //make former root the combined node

            //delete
            print_vector(min_heap);
            cout << "checkpoint 2.1" << endl;

            if (min_heap.size() > 3) {
                swap(min_heap, 2, min_heap.size() - 1); //swap former right child with last node
                min_heap.erase(prev(min_heap.end())); //erase last node after being moved
                heapify(min_heap, 2);  //heapify right sub-heap

                //delete
                print_vector(min_heap);
                cout << "checkpoint 2.2" << endl;
            } else { min_heap.erase(prev(min_heap.end())); }
        }

        //heapify entire min heap from root
        heapify(min_heap, 0);

        //delete
        print_vector(min_heap);
        cout << "checkpoint 3" << endl;

        cout << endl << endl;
    }

    //two (2) nodes left in min_heap
    combined = make_unique<Node>(min_heap[0]->val + min_heap[1]->val);
    combined->left = move(min_heap[0]);
    combined->right = move(min_heap[1]);
    unique_ptr <Node> test_root = move(combined);
    cout << "Huffman root val = " << test_root->val << endl << endl;
    min_heap.clear();
*/
/**********************************************************************************************************************/

//manually travesing Huffman tree
/**********************************************************************************************************************/
//cout << test_root -> val << endl;
//cout << test_root -> left -> val << endl;
//cout << (test_root -> left -> character).value() << endl;
//cout << test_root -> right -> val << endl;
//cout << test_root -> right -> left -> val << endl;
//cout << test_root -> right -> right -> val << endl;
//cout << test_root -> right -> left -> left -> val << endl;
//cout << (test_root -> right -> left -> left -> character).value() << endl;
//cout << test_root -> right -> left -> right -> val << endl;
//cout << (test_root -> right -> left -> right -> character).value() << endl;
//cout << test_root -> right -> right -> left -> val << endl;
//cout << (test_root -> right -> right -> left -> character).value() << endl;
//cout << test_root -> right -> right -> right -> val << endl;
//cout << (test_root -> right -> right -> right -> character).value() << endl;

/**********************************************************************************************************************/

//testing traversal and print_code
/**********************************************************************************************************************/
    /*
    unordered_map<char, string> m;
    traversal(test_root, "", m);
    for (const auto &p : m) { cout << "(" << p.first << ", " << p.second << "), "; }
    cout << endl;
     */
/**********************************************************************************************************************/


//    return 0;
//}

//}

//TEST_CASE("actual huffman_encoder functions") {

int main() {

    //generating text file that match test vector characters
    string file_name = "letters.txt";
    fstream file(file_name.c_str(), fstream::in);
    if (!file.is_open()) { throw runtime_error("File 1 is not open!"); }

    //test vector in pair mode
    vector <pair<char, unsigned>> freq = {{'A', 15},
                                          {'B', 7},
                                          {'C', 6},
                                          {'D', 6},
                                          {'E', 5},
    };
    for (const auto &p : freq)
        for (int i = 0; i < p.second; i++) { file << p.first; }

    //creating frequency_table object from based on test vector frequencies
    string s;
    char ch;
    while (file.get(ch)) { s += ch; }
    cout << "Contents of letters.txt: " << s << endl << endl;
    s.clear();
    file.close();

    frequency_table ft(file_name);
    cout << "Frequency:" << endl;
    for (const auto &p : freq) { cout << p.first << ": " << ft.get_frequency((char) p.first) << endl; }
    cout << endl;

    huffman_encoder he(ft);
    he.print_code();
    cout << endl;

    file_name = "encode.txt";
    fstream efile(file_name.c_str(), fstream::in | fstream::out | fstream::trunc);
    if (!efile.is_open()) { throw runtime_error("File 2 is not open!"); }
    efile << "CADBED";
    string decode_input = "1100101111100101";

    //simple encode-decode
    cout << "file content = ";
    efile.seekg(0);
    while(efile.get(ch)) { cout << ch; }
    cout << endl;
    string encoding = he.encode(file_name);
    cout << "CADBED encoded = " << encoding << endl;
    string decoding = he.decode(decode_input);
    cout << "CADBED decoded = " << decoding << endl << endl;
    efile.close();

    //invalid encode
    efile.open(file_name.c_str(), fstream::in | fstream::out | fstream::trunc);
    efile << "XYZ";
    cout << "file content = ";
    efile.seekg(0);
    while(efile.get(ch)) { cout << ch; }
    cout << endl;
    encoding = he.encode(file_name);
    cout << "XYZ encoded = " << encoding << endl << endl;
    efile.close();

    //yet another simple decode-encode
    efile.open(file_name.c_str(), fstream::in | fstream::out | fstream::trunc);
    efile << "BAD";
    decode_input = "1110101";
    cout << "file content = ";
    efile.seekg(0);
    while(efile.get(ch)) { cout << ch; }
    cout << endl;
    decoding = he.decode(decode_input);
    cout << "BAD decoded = " << decoding << endl;
    encoding = he.encode(file_name);
    cout << "BAD encoded = " << encoding << endl << endl;
    efile.close();

    return 0;
}

//}

