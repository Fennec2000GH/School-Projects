#include "huffman_encoder.h"
using namespace std;

//auxiliary functions
//swaps two (2) Node element within the same vector
void swap(vector<unique_ptr<Node>> &v, unsigned index1, unsigned index2) {
    //edge case: one or both indices out of range
    try {
        if (index1 < 0 || index1 >= v.size()) { throw out_of_range("index1 is out of range!"); }
        if(index2 < 0 || index2 >= v.size()) { throw out_of_range("index2 is out of range!"); }
    } catch (const out_of_range &error) {
        error.what();
        return;
    }

    //edge case: same index
    if(index1 == index2) { return; }

    unique_ptr<Node> temp = move(v[index2]);
    v[index2] = move(v[index1]);
    v[index1] = move(temp);
}

//gets parent index in binary tree
unsigned getParentIndex(unsigned index) {
    //edge case: index out of range
    if(index <= 0) { throw out_of_range("index is not large enough!"); }
    return floor((index - 1)/2);
}

//gets left child index in binary tree
unsigned getLeftChildIndex(unsigned index) { return 2 * index + 1; }

//gets right child index in binary tree
unsigned getRightChildIndex(unsigned index) { return 2 * index + 2; }

//heapify a vector into a mininum heap implementation
void heapify(vector<unique_ptr<Node>> &v, unsigned index) {
    //edge case: empty vector
    if(v.empty()) { return; }

    //edge case: single element vector
    if(v.size() == 1) { return; }

    //error: out_of_range index
    try { if(index >= v.size()) { throw out_of_range("index is too large!"); } }
    catch (const out_of_range &error) {
        error.what();
        return;
    }

    unsigned curr_index = index, smallerChildIndex;
    while(getLeftChildIndex(curr_index) < v.size()) {
        //both left and right child exists

        //delete
        cout << curr_index << ", ";

        if(getRightChildIndex(curr_index) < v.size()) {
            smallerChildIndex = *v[getLeftChildIndex(curr_index)] <= *v[getRightChildIndex(curr_index)] ?
                                getLeftChildIndex(curr_index) : getRightChildIndex(curr_index);
        } else { smallerChildIndex = getLeftChildIndex(curr_index); } //only left child exists

        //delete
        cout << smallerChildIndex << ", ";

        //swap with smaller child if and only if current Node is larger than smaller child
        if(*v[curr_index] > *v[smallerChildIndex]) {
            swap(v, curr_index, smallerChildIndex);
            curr_index = smallerChildIndex;

            //delete
            cout << "swap" << endl;
        }
        else {
            //delete
            cout << "no swap" << endl;

            return;
        }
    }
}

void build_heap(vector<unique_ptr<Node>> &v) {
    //edge case: empty vector
    if(v.empty()) { return; }

    //edge case: singleton element in vector
    if(v.size() == 1) { return; }

    unsigned last_non_leaf_index = getParentIndex(v.size() - 1);
    for(int i = last_non_leaf_index; i >= 0; i--) { heapify(v, i); } //heapifying
}

//prints each element in a vector of unique_ptr<Node>
void print_vector(const vector<unique_ptr<Node>> &v) {
    for (const auto &n : v) {
        if(n == nullptr) { cout << "(nullptr), "; }
        else if(!(n -> character).has_value()) { cout << "(internal, " << n->val << "), "; }
        else { cout << "(" << (n->character).value() << ", " << n->val << "), "; }
    }
    cout << endl;
}

//Node
//CONSTRUCTORS
Node::Node(unsigned new_val) : val(new_val) {
    character = nullopt;
    left.reset(nullptr);
    right.reset(nullptr);
}

Node::Node(unsigned new_val, char new_character) : val(new_val) {
    character.emplace(new_character);
    left.reset(nullptr);
    right.reset(nullptr);
}

//OPERATOR OVERLOADING
//note: only compares numerical value, not character
bool Node::operator == (const Node &n) const { return this -> val == n.val; }
bool Node::operator != (const Node &n) const { return this -> val != n.val; }
bool Node::operator <= (const Node &n) const { return this -> val <= n.val; }
bool Node::operator >= (const Node &n) const { return this -> val >= n.val; }
bool Node::operator < (const Node &n) const { return this -> val < n.val; }
bool Node::operator > (const Node &n) const { return this -> val > n.val; }

//huffman_encoder
//CONSTRUCTORS
huffman_encoder::huffman_encoder(const frequency_table &table) {
    unordered_set<char> char_set = table.get_characters();
    vector<unique_ptr<Node>> min_heap;

    //filtering character set only for non-zero frequency characters and then storing them inside a vector
    for(char ch : char_set) { if(table.get_frequency(ch) == 0) { char_set.erase(ch); } }

    //EDGE CASE: EMPTY TREE
    if(char_set.empty()) { return; }

    //EDGE CASE: SINGLE CHARACTER
    if(char_set.size() == 1) {
        code_map[*char_set.begin()] = "1";
        code_map_inv["1"] = *char_set.begin();
        return;
    }

    //delete
    transform(char_set.cbegin(), char_set.cend(), back_inserter(min_heap), [&table, &char_set] (char ch) { return make_unique<Node>(table.get_frequency(ch), ch); } );
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
    unique_ptr<Node> combined = nullptr;
    while(min_heap.size() > 2) {
        //left child of root is smaller than right child
        if(*min_heap[1] <= *min_heap[2]) {
            //creating new node with children being the two smallest nodes in min heap
            combined = make_unique<Node>(min_heap[0] -> val + min_heap[1] -> val);
            combined -> left = move(min_heap[0]);
            combined -> right = move(min_heap[1]);

            //delete
            cout << combined -> val << endl;

            min_heap.front() = move(combined); //make former root the combined node

            //delete
//            print_vector(min_heap);
//            cout << "checkpoint 1.1" << endl;

            swap(min_heap, 1, min_heap.size() - 1); //swap former left child with last node
            min_heap.erase(prev(min_heap.end())); //erase last node after being moved

            //heapify left sub-heap
            heapify(min_heap, 1);

            //delete
            print_vector(min_heap);
            cout << "checkpoint 1.2" << endl;

        } else { //right child of root is smaller than left child
            //creating new node with children being the two smallest nodes in min heap
            combined = make_unique<Node>(min_heap[0] -> val + min_heap[2] -> val);
            combined -> left = move(min_heap[0]);
            combined -> right = move(min_heap[2]);

            //delete
            cout << combined -> val << endl;

            min_heap.front() = move(combined); //make former root the combined node

            //delete
            print_vector(min_heap);
            cout << "checkpoint 2.1" << endl;

            if(min_heap.size() > 3) {
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
    combined = make_unique<Node>(min_heap[0] -> val + min_heap[1] -> val);
    combined -> left = move(min_heap[0]);
    combined -> right = move(min_heap[1]);
    unique_ptr<Node> test_root = move(combined);

    //delete
  cout << "Huffman root val = " << test_root -> val << endl << endl;

    min_heap.clear();
    traversal(test_root, "");
    test_root.reset();
}

//DESTRUCTORS
huffman_encoder::~huffman_encoder() { }

std::string huffman_encoder::get_character_code(char c) const {
    //delete
//    if(code_map.count(c) == 0) { cout << "get char code failed" << endl; }

    return code_map.count(c) > 0 ? code_map.at(c) : "";
}

std::string huffman_encoder::encode(const std::string &file_name) const {
    ifstream input;
    input.open(file_name.c_str(), fstream::in);
    if(!input.is_open()) { throw runtime_error("File not open!"); }
    stringstream ss;
    char ch;
    string code;

    //delete
//    cout << "encode checkpoint 1" << endl;

    while(input.get(ch)) {
        code = get_character_code(ch);

        //delete
//        cout << "encode while loop\t";
//        cout << ch << endl;

        if(code == "") {
            //delete
//            cout << "encode invalid char" << endl;

            return "";
        }
        ss << code;
    }
    //delete
//    cout << endl;

    return ss.str();

}

std::string huffman_encoder::decode(const std::string &string_to_decode) const {
    //edge case: empty string
    if(string_to_decode.empty()) {
        //delete
//        cout << "decode empty string" << endl;

        return "";
    }

    unsigned reader_index = 0; //marks start of new Huffman code; marks char index of current reading head
    string code; //possible Huffman code
    stringstream ss; // decoded string so far as a stringstream
    char ch; //current char where reader_index is located
    while(reader_index < string_to_decode.size()) {
        ch = string_to_decode[reader_index];
        if (ch != '0' && ch != '1') {
            //delete
//            cout << "decode not 0 or 1" << endl;

            return "";
        }
        code += ch;
        if(code_map_inv.find(code) != code_map_inv.end()) {
            ss << code_map_inv.at(code);
            code.clear();
        }

        //delete
//        cout << "(reader_index, bit): " << "(" << reader_index << ", " << ch << ") " << endl;

        ++reader_index;
    }

    //delete
//    cout << "decode string: " << ss.str() << endl;

    //unused and unrecognized Huffman code at the end of given string
    if(!code.empty()) {
        //delete
//        cout << "decode lagging tail" << endl;

        return "";
    }
    return ss.str();
}

//records all Huffman code in tree or sub-tree rooted at given unique_ptr
void huffman_encoder::traversal(const unique_ptr<Node> &ptr, string code) {
    //edge case: nullptr node
    if(ptr == nullptr) { return; }

    if(ptr -> left != nullptr) {
        traversal(ptr -> left, code += "0");
        code.erase(code.size() - 1, 1);
    }
    cout << (ptr -> val) << endl;
    if(ptr -> right != nullptr) {
        traversal(ptr -> right, code += "1");
        code.erase(code.size() - 1, 1);
    }
    if((ptr -> character).has_value()) {
        code_map.insert_or_assign((ptr -> character).value(), code);
        code_map_inv.insert_or_assign(code, (ptr -> character).value());
    }
}

//prints all available (char, Huffman code) pairs
void huffman_encoder::print_code() const {
    //edge case: no Huffman code available
    if(code_map.empty()) {
        cout << "Empty code map!" << endl;
        return;
    }

    for(const auto &p : code_map) { cout << "(" << p.first << ", " << p.second << "), "; }
    cout << endl;
}

//int main() { return 0; }