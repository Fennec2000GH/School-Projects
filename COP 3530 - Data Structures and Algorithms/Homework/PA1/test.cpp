
#include <iostream>
#include <vector>
#include "./project_files/bst.h"
#include "./project_files/student_db.h"
using namespace cop3530;
//int main(){
//    //create new binary search tree
//    bst<int, int> map;
//    std::cout << "Is the BST empty? " << map.empty() << ", size = " << map.size() << std::endl;
//
//    //insert elements to create balanced tree
//    int kv[3][2] = {{50, 0}, {25, 1}, {75, 2}};
//    for(int* p : kv) { map.insert(p[0], p[1]); }
//    std::cout << "Is the BST empty? " << map.empty() << ", size = " << map.size() << std::endl;
//
//    //confirm each key is present
//    bool containsKey = false;
//    for(int* p : kv) {
//        containsKey = map.contains(p[0]);
//        std::cout << "BST contains " << p[0] << "? " << containsKey << " ";
//        if(containsKey) { std::cout << ", value = " << map.at(p[0]) << std::endl; }
//    }
//
//    //confirm key is absent, and value does not exist
//    std::cout << "BST contains " << 80 << "? " << map.contains(80) << " " << std::endl << std::endl;
//    //std::cout << ", value = " << map.at(80) << std::endl;
//
//    map.erase(50);
//    std::cout << "Erased 50." << std::endl;
//    std::cout << "Is the BST empty? " << map.empty() << ", size = " << map.size() << std::endl << std::endl;
//
//    //erase non-existent key
//    //std::cout << "Erasing non-existent key 80" << std::endl;
//    //map.erase(80);
//
//    //inserting more nodes
//    std::cout << "Inserting 7 more nodes. " << std::endl;
//    map.insert(20, 3);
//    map.insert(30, 4);
//    map.insert(100, 2);
//    map.insert(110, 6);
//    map.insert(200, 200);
//    map.insert(180, 180);
//    map.insert(160, 160);
//    std::cout << "Is the BST empty? " << map.empty();
//    std::cout << ", size = " << map.size() << std::endl << std::endl;
//
//    //deleting node with only child
//    map.erase(100);
//    std::cout << "Erased 100." << std::endl;
//    std::cout << "Is the key 100 still in BST? " << map.contains(100) << std::endl;
//    std::cout << "Is the BST empty? " << map.empty() << ", size = " << map.size() << std::endl << std::endl;
//
//    //printing out pre_order and in_order contents
//    std::vector<std::pair<int, int>> preorderVec = map.preorder_contents();
//    std::vector<std::pair<int, int>> inorderVec = map.inorder_contents();
//
//    std::cout << "Pre-Order Contents: ";
//    for(std::pair<int, int> p : preorderVec) { std::cout << "(" << p.first << ", " << p.second << ")\t"; }
//    std::cout << std::endl;
//    std::cout << "In-Order Contents: ";
//    for(std::pair<int, int> p : inorderVec) { std::cout << "(" << p.first << ", " << p.second << ")\t"; }
//    std::cout << std::endl;

//
//    return 0;
//}

//LINE 88
//int main(){
//    cop3530::bst<int, int> map;
//    map.insert(1, 2);
//    map.insert(0, 0);
//    map.insert(2, 4);
//
//    //delete
//    for(std::pair<int, int> p : map.inorder_contents()) { std::cout << "(" << p.first << ", " << p.second << ")\t"; }
//    std::cout << std::endl;
//    for(std::pair<int, int> p : map.preorder_contents()) { std::cout << "(" << p.first << ", " << p.second << ")\t"; }
//    std::cout << std::endl;
//
//
//    map.erase(0);
//
//    //delete
//    for(std::pair<int, int> p : map.inorder_contents()) { std::cout << "(" << p.first << ", " << p.second << ")\t"; }
//    std::cout << std::endl;
//    for(std::pair<int, int> p : map.preorder_contents()) { std::cout << "(" << p.first << ", " << p.second << ")\t"; }
//    std::cout << std::endl;
//
//    std::vector<std::pair<int, int>> expected_inorder_contents = {{1, 2}, {2, 4}};
//    std::vector<std::pair<int, int>> expected_preorder_contents = {{1, 2}, {2, 4}};
//    std::cout << "97 CHECK inorder: " << (map.inorder_contents() == expected_inorder_contents) << std::endl;
//    std::cout << "98 CHECK preorder: " << (map.preorder_contents() == expected_preorder_contents) << std::endl;
//
//    map.erase(1);
//
//    //delete
//    for(std::pair<int, int> p : map.inorder_contents()) { std::cout << "(" << p.first << ", " << p.second << ")\t"; }
//    std::cout << std::endl;
//    for(std::pair<int, int> p : map.preorder_contents()) { std::cout << "(" << p.first << ", " << p.second << ")\t"; }
//    std::cout << std::endl;
//
//    expected_inorder_contents = {{2, 4}};
//    expected_preorder_contents = {{2, 4}};
//    std::cout << "103 CHECK inorder: " << (map.inorder_contents() == expected_inorder_contents) << std::endl;
//    std::cout << "104 CHECK preorder: " << (map.preorder_contents() == expected_preorder_contents) << std::endl;
//
//    map.erase(2);
//
//    //delete
//    std::cout << "Empty BST size = " << map.inorder_contents().size() << std::endl;
//    std::cout << "Empty BST size = " << map.preorder_contents().size() << std::endl;
//
//    expected_inorder_contents = {};
//    expected_preorder_contents = {};
//    std::cout << "109 CHECK inorder: " << (map.inorder_contents() == expected_inorder_contents) << std::endl;
//    std::cout << "110 CHECK preorder: " << (map.preorder_contents() == expected_preorder_contents) << std::endl;
//
//}

//LINE 169
//int main(){
//    cop3530::bst<int, int> map;
//
//    //delete
//    std::cout << "Empty BST size = " << map.size() << std::endl;
//
//    std::cout << "166 size == 0? " << (map.size() == 0) << std::endl;
//
//    map.insert(1, 2);
//    std::cout << "169 size == 1? " << (map.size() == 1) << std::endl;
//    map.insert(0, 0);
//    std::cout << "171 size == 2? " << (map.size() == 2) << std::endl;
//    map.insert(2, 4);
//    std::cout << "173 size == 3? " << (map.size() == 3) << std::endl;
//
//    map.erase(1);
//    std::cout << "176 size == 2? " << (map.size() == 2) << std::endl;
//    map.erase(0);
//    std::cout << "178 size == 1? " << (map.size() == 1) << std::endl;
//    map.erase(2);
//    std::cout << "180 size == 0? " << (map.size() == 0) << std::endl;
//}

//custom student_db test
int main(){
    student_db testDB;



    return 0;
}



//LINE 23 (student_db_test)
//int main(){
//
//
//
//
//    return 0;
//}