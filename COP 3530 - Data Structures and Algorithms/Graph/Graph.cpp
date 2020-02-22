#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include "Graph.h"
using namespace std;

//G R A P H      C L A S S
//CONSTRUCTORS
template <class G, class N>
Graph<G, N>::Graph(const G & identifier, const int & size):
id(identifier), numNodes(size) {
    V.resize(size);
    if(numNodes == 0)
        classification.push_back(GraphType::EMPTY);
    else if(numNodes == 1)
        classification.push_back(GraphType::SIMPLETON);
}

//DESTRUCTORS
template <class G, class N>
Graph<G, N>::~Graph() {
    V.clear();
}

//ACCESSORS
//returns the current id
template <class G, class N>
G Graph<G, N>::getID() const {
    return id;
}

//returns the current number of Node<N> objects in set V
template <class G, class N>
int Graph<G, N>::getSize() const {
    return Graph<G, N>::numNodes;
}

//returns the degree of the i^th Node<N> object in set V (-1 if nonexistent)
template <class G, class N>
int Graph<G, N>::getDegree(const int & i) const {
    if(i >= 1 && i <= V.size())
        return V.at(i - 1).getDegree();
    return -1;
}

//returns the degree of the Node<N> object with the given ID (-1 if nonexistent)
template <class G, class N>
int Graph<G, N>::getDegree(const N & identifier) const {
    auto it = find_if(V.begin(), V.end(), [identifier](Node<N> n){return n.getID == identifier;});
    if(it != V.end())
        return it -> getDegree();
    return -1;
}

//traverses the entire graph by depth (assuming there is only one intact graph)
template <class G, class N>
void Graph<G, N>::TBDepth(const Node<N> & start, vector<Node<N>> & v) const {
    start.setFlag(false);
    for(auto & ptr : start.links)
        if(ptr -> flag != false)
            traverseByDepth(*ptr, v);
    v.push_back(start);
    return;
}

//traverses the entire graph by depth (assuming there is only one intact graph)
template <class G, class N>
void Graph<G, N>::TBBreadth(Node<N> & start, vector<Node<N>> & v) const {
    queue<Node<N>> q;
    start.setFlag(false);
    q.push(start);
    while(q.empty() == false){
        Node<N> temp = q.pop();
        for(auto & ptr : temp.links)
            if(ptr -> getFlag != false){
                ptr -> setFlag(false);
                q.push(*ptr);
            }
        v.push_back(temp);
    }

    return;
}

//MUTATORS
//sets a new id
template <class G, class N>
void Graph<G, N>::setID(const G & identifier) {
    id = identifier;
    return;
}

//sets a space in set V to specify a certain number of Node<N> objects will occupy the set
template <class G, class N>
void Graph<G, N>::setSize(const int & size) {
    Graph<G, N>::numNodes = size;
    V.resize(size);
    return;
}

//inserts new Node<T> object into the graph
template <class G, class N>
void Graph<G, N>::addNode(const Node<N> & n) {
    V.push_back(n);
    return;
}

//deletes the Node<N> object in set V with a specified ID
template <class G, class N>
void Graph<G ,N>::deleteNode(const N & identifier) {
    auto it = find_if(V.begin(), V.end(), [identifier](Node<N> n){return n.getID() == identifier;});
    if(it != V.end())
        V.erase(it);
    return;
}

//deletes the i^th Node<N> object in set V
template <class G, class N>
void Graph<G, N>::deleteNode(const int & i) {
    if(i < 1 || i > V.size())
        return;
        auto it = next(V.begin(), i - 1);
    V.erase(it);
    return;
}

//C O M P L E T E      G R A P H      C L A S S
//CONSTRUCTORS
template <class G, class N>
CompleteGraph<G, N>::CompleteGraph(const G & identifier, const int & size):
Graph<G, N>(identifier, size), centerDegree(size - 1) {
    Graph<G, N>::classification.push_back(GraphType::COMPLETE);
}

//ACCESSORS
//returns the total number of edges
template <class G, class N>
int CompleteGraph<G, N>::getEdges() const {
    int sides = Graph<G, N>::getSize();
    int diagonals = getDiagonals();
    return sides + diagonals;
}

//returns the number of unique diagonals from one Node<N> object to another (polygon sides are excluded)
template <class G, class N>
int CompleteGraph<G, N>::getDiagonals() const {
    int size = Graph<G, N>::getSize();
    if(size < 4)
        return 0;
    else
        return size * (size - 3) / 2;
}

//C Y C L E      C L A S S
//CONSTRUCTORS
template <class G, class N>
Cycle<G, N>::Cycle(const G & identifier):
Graph<G, N>(identifier) {
    Graph<G, N>::classification.push_back(GraphType::CYCLE);
    if(Graph<G, N>::numNodes == 0)
        Graph<G, N>::classification.push_back(GraphType::EMPTY);
    else if(Graph<G, N>::numNodes == 1)
        Graph<G, N>::classification.push_back(GraphType::SIMPLETON);
}

//D I G R A P H      C L A S S
//CONSTRUCTORS
template <class G, class N>
Digraph<G, N>::Digraph(const G & identifier):
Graph<G, N>(identifier) {
    Graph<G, N>::classification.push_back(GraphType::DIGRAPH);
    if(Graph<G, N>::numNodes == 0)
        Graph<G, N>::classification.push_back(GraphType::EMPTY);
    else if(Graph<G, N>::numNodes == 1)
        Graph<G, N>::classification.push_back(GraphType::SIMPLETON);
}

//W E I G H T E D      G R A P H      C L A S S
//CONSTRUCTORS
template <class G, class N>
WeightedGraph<G, N>::WeightedGraph(const G & identifier, const int & size):
Graph<G, N>(identifier, size) {
    Graph<G, N>::classification.push_back(GraphType::WEIGHTED);
    if(Graph<G, N>::numNodes == 0)
        Graph<G, N>::classification.push_back(GraphType::EMPTY);
    else if(Graph<G, N>::numNodes == 1)
        Graph<G, N>::classification.push_back(GraphType::SIMPLETON);
}


//ACCESSORS



//MUTATORS

//W H E E L      C L A S S
//CONSTRUCTORS
template <class G, class N>
Wheel<G, N>::Wheel(const G & identifier, const int & size, Node<N> & n):
Graph<G, N>(identifier, size), center(n) {
    Graph<G, N>::V.insert(n);
    Graph<G, N>::classification.push_back(GraphType::WHEEL);
    if(Graph<G, N>::numNodes == 0)
        Graph<G, N>::classification.push_back(GraphType::EMPTY);
    else if(Graph<G, N>::numNodes == 1)
        Graph<G, N>::classification.push_back(GraphType::SIMPLETON);
}

//ACCESSORS
//returns the degree of the i^th Node<N> object in set V (-1 if nonexistent)
template <class G, class N>
int Wheel<G, N>::getDegree(const int & i) const {
    int size = Graph<G, N>::getDegree();
    if(i > size)
        return -1;
    else if(size == 0)
        return 0;
    else if((size >= 1 && size <= 3) || Graph<G, N>::V.at(i - 1) == center)
        return size - 1;
    else
        return 3;
}

//returns the degree of the Node<N> object with the given ID (-1 if nonexistent)
template <class G, class N>
int Wheel<G, N>::getDegree(const N & identifier) const {
    Graph<G, N>::getDegree(identifier);
}

//MUTATORS
//inserts new Node<T> object into the graph
template <class G, class N>
void Wheel<G, N>::addNode(const Node<N> & n) {
    Graph<G, N>::V.push_back(n);
    return;
}
