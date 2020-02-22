#pragma once
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
    if (root == nullptr) { root = new node(key, t); return; }

    node *current = root;
    //decision on going left or right at each node in insertion path
    while (key != current->key) {
        if (key < current->key) {
            if (current->left_child == nullptr) break;
            else { current = current->left_child; continue; }
        } else if (key > current->key) {
            if (current->right_child == nullptr) break;
            else { current = current->right_child; continue; }
        }
    }

    //final turn, whether to insert as left or right child or replace value
    if (key == current->key) { current->value = t; }
    else if (key < current->key) { current->left_child = new node(key, t); }
    else { current->right_child = new node(key, t); }
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

} // namespace cop3530