#ifndef SIMPLE_GRAPH
#define SIMPLE_GRAPH
#include <set>
#include <string>
#include <vector>
#include "Auxiliary.h"
using namespace std;

//U N D I R E C T E D      G R A P H
enum class GraphType {COMPLETE, CYCLE, DIGRAPH, EMPTY, SIMPLETON, TREE, WEIGHTED, WHEEL};
template <class G = string, class N = string>
class Graph {
public:
    //CONSTRUCTORS
    Graph(const G & identifier, const int & size = 0);

    //DESTRUCTORS
    ~Graph();

    //ACCESSORS
    G getID() const;
    int getSize() const;
    virtual int getDegree(const int & i) const;
    virtual int getDegree(const N & identifier) const;
    void TBDepth(const Node<N> & start, vector<Node<N>> & v) const;
    void TBBreadth(Node<N> & start, vector<Node<N>> & v) const;

    //MUTATORS
    void setID(const G & identifier);
    void setSize(const int & size);
    virtual void addNode(const Node<N> & n);
    virtual void deleteNode(const N & identifier);
    virtual void deleteNode(const int & i);

protected:
    G id;
    int numNodes;
    set<Node<N>> V;
    vector<GraphType> classification;

};

//C O M P L E T E      G R A P H
template <class G = string, class N = string>
class CompleteGraph : public Graph<G, N> {
public:
    //CONSTRUCTORS
    CompleteGraph(const G & identifier, const int & size = 1);

    //ACCESSORS
    int getEdges() const;
    int getDiagonals() const;

    //MUTATORS
    void addNode(const Node<N> & n); 
    void deleteNode(const N & identifier);
    void deleteNode(const int & i);

private:
    int centerDegree;

};

//C Y C L E
template <class G = string, class N = string>
class Cycle : public Graph<G, N> {
public:
    //CONSTRUCTORS
    Cycle(const G & identifier);

    //ACCESSORS


    //MUTATORS
    void addNode(const Node<N> & n);
    void deleteNode(const N & identifier);
    void deleteNode(const int & i);

private:

};

//D I G R A P H
template <class G = string, class N = string>
class Digraph : public Graph<G, N> {
public:
    //CONSTRUCTORS
    Digraph(const G & identifier);

    //ACCESSORS

    //MUTATORS
    void addNode(const Node<N> & n);
    void deleteNode(const N & identifier);
    void deleteNode(const int & i);

private:

};

//W E I G H T E D      G R A P H
template <class G = string, class N = string>
class WeightedGraph : public Graph<G, N> {
public:
    //CONSTRUCTORS
    WeightedGraph(const G & identifier, const int & size);

    //ACCESSORS

    //MUTATORS
    void addNode(const Node<N> & n);
    void deleteNode(const N & identifier);
    void deleteNode(const int & i);

private:

};

//W H E E L
template <class G = string, class N = string>
class Wheel : public Graph<G, N> {
public:
    //CONSTRUCTORS
    Wheel(const G & identifier, const int & size = 0, Node<N> & n = Graph<G, N>::V.front());

    //DESTRUCTORS
    ~Wheel();

    //ACCESSORS
    int getDegree(const int & i) const;
    int getDegree(const N & identifier) const;

    //MUTATORS
    void addNode(const Node<N> & n);
    void deleteNode(const N & identifier);
    void deleteNode(const int & i);

private:
    Node<N> center;

};



#endif
