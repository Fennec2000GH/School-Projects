#include <iostream>
#include <iterator>
#include "Auxiliary.h"
using namespace std;

//S M A R T      P O I N T E R      C L A S S
template <class P>
smart_ptr<P>::smart_ptr(P * pointer): ptr(pointer) {}

template <class P>
smart_ptr<P>::~smart_ptr() {
    delete ptr;
}

template <class P>
P smart_ptr<P>::operator * () {
    return *ptr;
}

//N O D E      C L A S S
//CONSTRUCTORS
template <class N>
Node<N>::Node(const N & identifier, const double & w, const int & size, const bool & b):
id(identifier), weight(w), flag(b) {
    links.resize(size);
}

//DESTRUCTORS
template <class N>
Node<N>::~Node() {
    links.clear();
}

//ACCESSORS
//returns the current id
template <class N>
N Node<N>::getID() const {
    return id;
}

//returns the number of entries in links, regardless of the Node<N> object's degree
template <class N>
int Node<N>::getLinkSize() const {
    return links.size();
}

//returns the exact degree of the Node<N> object
template <class N>
int Node<N>::getDegree() const {
    int degree;
    for(auto edge : links){
        if(edge -> getEdgeType() == EdgeType::MULTI)
            degree += edge -> getMultiSize();
        else
            ++degree;
    }
    return degree;
}

//returns the current flag status
template <class N>
bool Node<N>::getFlag() const {
    return flag;
}

//MUTATORS
//sets a new id
template <class N>
N Node<N>::setID(const N & identifier) {
    id = identifier;
}

//connects an edge to another Node<T> object
template <class N>
void Node<N>::addLink(Node<N> * ptr) {
    links.push_back(new UndirectedEdge<N>());
    links.back().setEdge(this, ptr);
    return;
}

//removes the i^th edge from the Node<T> object
template <class N>
void Node<N>::deleteLink(const int & i) {
    auto it = links.begin();
    advance(it, i - 1);
    links.erase(it);
    return;
}

//sets a specified boolean value to "flag"
template <class N>
void Node<N>::setFlag(const bool & b) {
    flag = b;
    return;
}

//reverses the boolean value in "flag"
template <class N>
void Node<N>::tickFlag() {
    flag = !flag;
    return;
}

//E D G E      C L A S S
//CONSTRUCTORS
template <class N>
Edge<N>::Edge(const double & w,  EdgeType et):
weight(w), classification(et) {}

//ACCESSORS
//returns the current weight on the Edge<N> object
template <class N>
double Edge<N>::getWeight() const {
    return weight;
}

//returns the EdgeType
template <class N>
EdgeType Edge<N>::getEdgeType() const {
    return classification; 
}

//MUTATORS
//resets the weight
template <class N>
void Edge<N>::setWeight(const double & w) {
    weight = w;
    return;
}

//UNDIRECTED EDGE
//CONSTRUCTORS
template <class N>
UndirectedEdge<N>::UndirectedEdge(Node<N> * u, Node<N> * v, const double & w):
Edge<N>(w, EdgeType::UNDIRECTED) {
    node_pair.first = u;
    node_pair.second = v;
    v -> links.push_back(this);

}

//ACCESSORS
//returns the ID of the only Node<N> object *this is connected with by an edge
template <class N>
N UndirectedEdge<N>::getOtherNodeID() const {
    if(node_pair.first != this)
        return node_pair.first -> getID();
    else
        return node_pair.second -> getID();
}

//returns a copy of the Node<N> object *this is linked with an edge
template <class N>
Node<N> UndirectedEdge<N>::getOtherNode() const {
    if(node_pair.first != this)
        return *node_pair.first;
    else
        return *node_pair.second;
}

//DIRECTED EDGE
//CONSTRUCTORS
template <class N>
DirectedEdge<N>:: DirectedEdge(Node<N> * v, const double & w):
Edge<N>(w, EdgeType::DIRECTED) {
    p = v;
}

//ACCESSORS
//returns the neighboring Node<N> object's ID
template <class N>
N DirectedEdge<N>::getOtherNodeID() const {
    return p -> getID();
}

//returns a copy of the neighboring Node<N> object
template <class N>
Node<N> DirectedEdge<N>::getOtherNode() const {
    return *p;
}

//MULTIGRAPH EDGE
//CONSTRUCTORS
template <class N>
Multi<N>::Multi(Node<N> * v, const int & count):
Edge<N>(0, EdgeType::MULTI) {
    for(unsigned int i = 0; i < count; i++)
        edges.push_back({v, 0});
}

//ACCESSORS
//returns the count of edges directed towards the same Node<N> object, as located in edgestor edges
template <class N>
int Multi<N>::getMultiSize() const {
    return edges.size();
}

//returns the neighboring Node<N> object's ID
template <class N>
N Multi<N>::getOtherNodeID() const {
    return edges.front() -> getID();
}

//returns a copy of the neighboring Node<N> object
template <class N>
Node<N> Multi<N>::getOtherNode() const {
    return *edges.front();
}

//MUTATORS
//sets the same weight for all existing edges in the multiedge
template <class N>
void Multi<N>::setAllWeight(const double & w) {
    for(auto & e : edges)
        e.second = w;
}

//set the i^th edge in the multiedge to a specified weight
template <class N>
void Multi<N>::setOneWeight(const int & i, const double & w) {
    if(i < 1 || i > edges.size())
        return;
    edges.at(i - 1).second = w;
}
