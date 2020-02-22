#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
#include <exception>
#include <stdexcept>

namespace cop3530 {

template <typename Key, typename T>
class bst {
private:
    //VARIABLES
    struct node {
        //VARIABLES
        Key key;
        T value;
        node *left_child;
        node *right_child;

        //CONSTRUCTORS
        node() { left_child = nullptr; right_child = nullptr; }

        node(Key k, T t) : key(k), value(t) { left_child = nullptr; right_child = nullptr; }

        //DESTRUCTORS
        ~node() { left_child = nullptr; right_child = nullptr; }
    };

    //balance factor records
    std::vector<int> bf;

    //root of tree
    node *root;

public:
    bst();
    ~bst();
    void insert(const Key &key, const T &t);
    void erase(const Key &key);
    void erase(const Key &key, node &start, node &parent);
    T &at(const Key &key) const;
    bool contains(const Key &key) const;
    bool empty() const;
    size_t size() const;
    std::vector<std::pair<Key, T>> inorder_contents();
    std::vector<std::pair<Key, T>> preorder_contents();
    void inorder_traversal(std::vector<std::pair<Key, T>> &c, const node &start) const;
    void preorder_traversal(std::vector<std::pair<Key, T>> &c, const node &start) const;
    int countChildren(const node &n) const;
    struct bst<Key, T>::node* inorderSuccessor(const node &start) const;
    struct bst<Key, T>::node* getParent(const node &start, const node &target);
    int getHeight(const node& start) const;
    int getBalanceFactor(const node& start) const;
    int getParentIndex(int index) const;
    void left_left_rotate(node* curr_node);
    void left_right_rotate(node* curr_node);
    void right_left_rotate(node* curr_node);
    void right_right_rotate(node* curr_node);

};

template <typename Key, typename T>
bst<Key, T>::bst() { root = nullptr; }

template <typename Key, typename T>
bst<Key, T>::~bst() {
    //edge case: empty tree
    if (empty()) { return; }
    std::queue<node *> deleteQ;
    deleteQ.push(root);
    node *top;

    //deallocate child pointers using BFS
    while (!deleteQ.empty()) {
        top = deleteQ.front();
        deleteQ.pop();
        if (top->left_child != nullptr) { deleteQ.push(top->left_child); }
        if (top->right_child != nullptr) { deleteQ.push(top->right_child); }
        delete top;
    }
}

template <typename Key, typename T>
void bst<Key, T>::insert(const Key &key, const T &t) {
    //edge case: empty tree
    if (empty()) { root = new node(key, t); bf.push_back(0); return; }

    node *current = root;
    int index = 0; //index of array-based binary tree used to locate the balance factor in bf

    //decision on going left or right at each node in insertion path
    while (key != current->key) {
        if (key < current->key) {
            if (current->left_child == nullptr) break;
            else { current = current->left_child; index = index * 2 + 1; continue; }
        } else if (key > current->key) {
            if (current->right_child == nullptr) break;
            else { current = current->right_child; index = index * 2 + 2; continue; }
        }
    }

    //final turn, whether to insert as left or right child or replace value
    if (key == current->key) { current->value = t; }
    else if (key < current->key) { current->left_child = new node(key, t); index = index * 2 + 1; }
    else { current->right_child = new node(key, t); index = index * 2 + 2; }

    //adjusting balance factors for all nodes in ancestor path up to root
    bool direction[2]; //climbing up the ancestral path, left child -> parent = true, right child -> parent = false
    bf[index] = 0;
    direction[0] = index % 2 == 1;

    //edge case: height of tree is 1
    if(getHeight(*root) == 1) { bf[getParentIndex(index)] += index % 2 == 0 ? 1 : -1; return; }

    //computing balance factor for grandparent of inserted node
    index = getParentIndex(index);
    bf[index] = getBalanceFactor(*current);
    direction[1] = index % 2 == 1;

    while(true) {
        index = getParentIndex(index);
        current = getParent(*root, *current);
        bf[index] = getBalanceFactor(*current);
        if(current == root || abs(bf[index]) > 1) { break; }
        direction[0] = direction[1];
        direction[1] = index % 2 == 1;
    }

    //reaches first unbalanced node
    if(abs(bf[index]) > 1) {
        std::string last2moves = std::to_string(direction[1]) + std::to_string(direction[0]);
        switch (last2moves) {
            case "00" : { left_left_rotate(current); break; }
            case "01" : { right_left_rotate(current); break; }
            case "10" : { left_right_rotate(current); break; }
            case "11" : { right_right_rotate(current); }
        }
    }
}

template <typename Key, typename T>
void bst<Key, T>::erase(const Key &key) { erase(key, *root, *root); }

template <typename Key, typename T>
void bst<Key, T>::erase(const Key &key, node &start, node &parent) {
    //pointers representing parent and child during traversal search for key
    node *prev = &parent; //pointer to parent of root of subtree to start search first
    node *current = &start; //root of subtree to search and delete node with given key

    //edge case: empty tree
    if(empty()) { throw std::out_of_range("BST is empty!"); }

    //edge case: the root is to be deleted, so there is no true parent (prev) above the root
    if(root == &start && root -> key == key) {
        if(countChildren(*root) == 0) { delete root; root = nullptr; return; }
        else if(countChildren(*root) == 1) {
            node * onlyChild = root -> left_child != nullptr ? root -> left_child : root -> right_child;
            delete root;
            root = onlyChild;
            return;
        }
        //root has 2 children, so root will be replaced with its inorder successor (exists) in switch statement later
    }

    //std::cout << "root's key = " << current -> key << "\troot's value = " << current -> value << std::endl;
    //if(current -> key == key) { std::cout << "get the root" << std::endl; }
    //prev is parent of current when current matches the given key
    while (key != current->key) {
        prev = current;
        //std::cout << current -> value << std::endl;
        if (key < current->key) {
            if (current->left_child == nullptr) { throw std::out_of_range("Key not found!"); }
            else { current = current->left_child; }
        } else if (key > current->key) {
            if (current->right_child == nullptr) { throw std::out_of_range("Key not found!"); }
            else { current = current->right_child; }
        }
    }

    //checks the number of children target node has
    int numChild = countChildren(*current);
    //std::cout << "# children = " << numChild << std::endl;
    switch (numChild) {
        case 0: {
            if(current == root) { delete root; root = nullptr; return; }
            if (prev->left_child == current) { delete prev -> left_child; prev -> left_child = nullptr; return; }
            else { delete prev -> right_child; prev -> right_child = nullptr; return; }
            break;
        }
        case 1: {
            node *onlyChild = current->left_child != nullptr ? current->left_child : current->right_child;
            if (prev -> left_child == current) { delete prev->left_child; prev->left_child = onlyChild; }
            else { delete prev -> right_child; prev -> right_child = onlyChild; return; }
            break;
        }
        case 2: {
            //pointer to inorder successor of node to be deleted
            node *inorder = inorderSuccessor(*current);
            //std::cout << "inorder successor: key = " << inorder -> key << ", value = " << inorder -> value << std::endl;
            current -> key = inorder -> key; current -> value = inorder -> value;
            erase(inorder -> key, *inorder, *getParent(*current, *inorder));
            break;
        }
        default: { throw std::out_of_range("Number of children must be from 0 to 2 (inclusive)!"); }
    }
}

template <typename Key, typename T>
T &bst<Key, T>::at(const Key &key) const {
    //edge case: empty tree
    if (empty()) { throw std::out_of_range("Tree is empty!"); }

    //decision on going left or right at each node in insertion path
    node *current = root;
    while(key != current -> key) {
        if (key < current->key) {
            if (current->left_child == nullptr) { throw std::out_of_range("Key does not exist!"); }
            else { current = current->left_child; continue; }
        } else if (key > current->key) {
            if (current->right_child == nullptr) { throw std::out_of_range("Key does not exist!"); }
            else { current = current->right_child; continue; }
        }
    }
    return current -> value;
}

template <typename Key, typename T>
bool bst<Key, T>::contains(const Key &key) const {
    //edge case: empty tree
    if(empty()) { return false; }

    node * current = root;
    while(key != current -> key){
        if(key < current -> key) {
            if(current -> left_child == nullptr) { return false; }
            else { current = current -> left_child; continue; }
        } else {
            if(current -> right_child == nullptr) { return false; }
            else { current = current -> right_child; continue; }
        }
    }
    return true;
}

template <typename Key, typename T>
bool bst<Key, T>::empty() const { return root == nullptr; }

template <typename Key, typename T>
size_t bst<Key, T>::size() const {
    //edge case: empty tree
    if (empty()) { return 0; }

    //uses BFS to count number of nodes
    long counter = 0;
    std::queue<const node *> nodeQ;
    const node * top = root;
    nodeQ.push(top);
    while (!nodeQ.empty()) {
        ++counter;
        top = nodeQ.front();
        nodeQ.pop();
        if (top->left_child != nullptr) { nodeQ.push(top->left_child); }
        if (top->right_child != nullptr) { nodeQ.push(top->right_child); }
    }
    return std::size_t(counter);
}

template <typename Key, typename T>
std::vector<std::pair<Key, T>> bst<Key, T>::inorder_contents() {
    std::vector<std::pair<Key, T>> contents;
    if(!empty()) { inorder_traversal(contents, *root); }
    return contents;
}

template <typename Key, typename T>
std::vector<std::pair<Key, T>> bst<Key, T>::preorder_contents() {
    std::vector<std::pair<Key, T>> contents;
    if(!empty()) { preorder_traversal(contents, *root); }
    return contents;
}

//auxiliary function appends nodes to the same vector using inorder traversal
template <typename Key, typename T>
void bst<Key, T>::inorder_traversal(std::vector<std::pair<Key, T>> &c, const node &start) const {
    if (start.left_child != nullptr) { inorder_traversal(c, *(start.left_child)); }
    c.push_back(std::pair<Key, T>(start.key, start.value));
    if (start.right_child != nullptr) { inorder_traversal(c, *(start.right_child)); }
}

//auxiliary function appends nodes to the same vector using inorder traversal
template <typename Key, typename T>
void bst<Key, T>::preorder_traversal(std::vector<std::pair<Key, T>> &c, const node &start) const {
    c.push_back(std::pair<Key, T>(start.key, start.value));
    if (start.left_child != nullptr) { preorder_traversal(c, *(start.left_child)); }
    if (start.right_child != nullptr) { preorder_traversal(c, *(start.right_child)); }
}

//counts number of children
template <typename Key, typename T>
int bst<Key, T>::countChildren(const node &n) const {
    int numChild = 0;
    if (n.left_child != nullptr) { ++numChild; }
    if (n.right_child != nullptr) { ++numChild; }
    return numChild;
}

//finds inorder successor
template <typename Key, typename T>
struct bst<Key, T>::node* bst<Key, T>::inorderSuccessor(const node &start) const {
    node *current = const_cast<node *>(&start);
    if (current->right_child == nullptr) { throw std::out_of_range("Needs a right subtree!"); }
    current = current->right_child;
    while (current->left_child != nullptr) { current = current->left_child; }
    return current;
}

//finds parent node of given node, and returns nullptr if not found
template <typename  Key, typename  T>
struct bst<Key, T>::node* bst<Key, T>::getParent(const node &start, const node &target){
    if(&start == &target) { return nullptr; }
    const node *current = &start;
    Key targetKey = target.key;
    while(current -> left_child != &target && current -> right_child != &target) {
        if(targetKey < current -> key) {
            if(current -> left_child == nullptr) { return nullptr; }
            else { current = current -> left_child; continue; }
        } else {
            if(current -> right_child == nullptr) { return nullptr; }
            else { current = current -> right_child; continue; }
        }
    }
    return const_cast<node *>(current);
}

//finds the height of tree or subtree rooted at specified node (height is measure by edge length of longest path)
template <typename Key, typename T>
int bst<Key, T>::getHeight(const node &start) const {
    //edge case: singleton node
    if(start.left_child == nullptr && start.right_child == nullptr) return 0;

    if(start.left_child == nullptr) { return 1 + getHeight(*start.right_child); }
    else if(start.right_child == nullptr) { return 1 + getHeight(*start.left_child); }
    return 1 + std::max(getHeight(*start.left_child), getHeight(*start.right_child));
}

//computes the balance factor at a given node as the root of the tree or subtree
template <typename Key, typename T>
int bst<Key, T>::getBalanceFactor(const node &start) const {
    //edge case: singleton node
    if(start.left_child == nullptr && start.right_child == nullptr) return 0;

    if(start.left_child == nullptr) return getHeight(*start.right_child);
    else if(start.right_child == nullptr) return - getHeight(*start.left_child);
    return getHeight(*start.right_child) - getHeight(*start.left_child);
}

//finds parent index of array-based binary tree
template <typename Key, typename T>
int bst<Key, T>::getParentIndex(int index) const {
    //edge case: index is out of bounds i.e. 0 or negative
    if(index <= 0) throw std::out_of_range("Index must be positive!");
    return floor((index - 1) / 2.0);
}

template <typename Key, typename T>
void bst<Key, T>::left_left_rotate(node* curr_node) {
    //edge case: null node
    if(curr_node == nullptr) throw std::out_of_range("Current node must not be null!");

    //prerequisite: missing right child
    if(curr_node -> right_child == nullptr) throw std::out_of_range("Current node must have non-null right child!");

    //parent of g that does not change except switch a child form g to p
    node* subRoot = curr_node == root ? nullptr : getParent(root, curr_node);
    node* g = curr_node; //grandparent of presumably inserted node that causes unbalance
    node* p = g -> right_child;
    g -> right_child = p -> left_child;
    p -> left_child = g;
    if(subRoot != nullptr) {
        if(subRoot -> left_child == g) { subRoot -> left_child = p; }
        else { subRoot -> right_child = p; }
    } else { root == p; }
}

template <typename Key, typename T>
void bst<Key, T>::right_left_rotate(node* curr_node) {
    //edge case: null node
    if(curr_node == nullptr) throw std::out_of_range("Current node must not be null!");

    //prerequisite: missing right child
    if(curr_node -> right_child == nullptr) throw std::out_of_range("Current node must have non-null right child!");

    //prerequisite: missing right-left grandchild
    if(curr_node -> right_child -> left_child == nullptr) throw std::out_of_range("Current node must have non-null left-right grandchild!");

    //parent of g that does not change except switch a child form g to p
    node* subRoot = curr_node == root ? nullptr : getParent(root, curr_node);
    node* g = curr_node; //grandparent of presumably inserted node that causes unbalance
    node* p = g -> right_child;
    right_right_rotate(p);
    left_left_rotate(g);
}

template <typename Key, typename T>
void bst<Key, T>::left_right_rotate(node* curr_node) {
    //edge case: null node
    if(curr_node == nullptr) throw std::out_of_range("Current node must not be null!");

    //prerequisite: missing left child
    if(curr_node -> left_child == nullptr) throw std::out_of_range("Current node must have non-null left child!");

    //prerequisite: missing left-right grandchild
    if(curr_node -> left_child -> right_child == nullptr) throw std::out_of_range("Current node must have non-null right-left grandchild!");

    //parent of g that does not change except switch a child form g to p
    node* subRoot = curr_node == root ? nullptr : getParent(*root, *curr_node);
    node* g = curr_node; //grandparent of presumably inserted node that causes unbalance
    node* p = g -> left_child;
    left_left_rotate(p);
    right_right_rotate(g);
}

template <typename Key, typename T>
void bst<Key, T>::right_right_rotate(node* curr_node) {
    //edge case: null node
    if(curr_node == nullptr) throw std::out_of_range("Current node must not be null!");

    //prerequisite: missing left child
    if(curr_node -> left_child == nullptr) throw std::out_of_range("Current node must have non-null left child!");

    //parent of g that does not change except switch a child form g to p
    node* subRoot = curr_node == root ? nullptr : getParent(*root, *curr_node);
    node* g = curr_node;
    node* p = g -> left_child;
    g -> left_child = p -> right_child;
    p -> right_child = g;
    if(subRoot != nullptr){
        if(subRoot -> left_child == g) { subRoot -> left_child = p; }
        else { subRoot -> right_child = p; }
    } else { root = p; }
}

} // namespace cop3530 

