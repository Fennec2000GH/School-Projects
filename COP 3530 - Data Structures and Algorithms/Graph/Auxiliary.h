#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
using namespace std;

//S M A R T      P O I N T E R
template <class P>
class smart_ptr {
public:
    //rapper for raw pointer
    explicit smart_ptr(P * pointer);
    ~smart_ptr();
    P operator * ();

    //raw pointer
    P * ptr;
};

//N O D E
template <class N>
class Edge;

template <class N = string>
class Node {
public:
    template <class G = string, class n = string>
    friend class Graph;

    //CONSTRUCTORS
    Node(const N & identifier, const double & w = 0, const int & size = 0, const bool & b = true);

    //DESTRUCTORS
    ~Node();

    //ACCESSORS
    N getID() const;
    int getLinkSize() const;
    int getDegree() const;
    bool getFlag() const;

    //MUTATORS
    N setID(const N & identifier);
    void addLink(Node<N> * ptr);
    void deleteLink(const int & i);
    void setFlag(const bool & b);
    void tickFlag();

protected:
    N id;
    bool flag;
    double weight;
    vector<Edge<N>*> links;

};


//E D G E
template <class N = string>
using node_ptr = smart_ptr<Node<N>>;
enum class EdgeType {UNDIRECTED, DIRECTED, MULTI};

template <class N = string>
class Edge {
public:
    //CONSTRUCTORS
    Edge(const double & w = 0, EdgeType et = EdgeType::UNDIRECTED);

    //DESTRUCTORS
    virtual ~Edge();

    //ACCESSORS
    double getWeight() const;
    EdgeType getEdgeType() const;
    virtual N getOtherNodeID() const = 0;
    virtual Node<N> getOtherNode() const = 0;

    //MUTATORS
    void setWeight(const double & w);

protected:
    double weight;
    EdgeType classification; 

};

//UNDIRECTED EDGE
template <class N = string>
class UndirectedEdge {
public:
    //CONSTRUCTORS
    UndirectedEdge(Node<N> * u, Node<N> * v, const double & w = 0);

    //ACCESSORS
    N getOtherNodeID() const;
    Node<N> getOtherNode() const;

private:
    pair<node_ptr<N>, node_ptr<N>> node_pair;

};

//DIRECTED EDGE
template <class N = string>
class DirectedEdge : public Edge<N> {
public:
    //CONSTRUCTORS
    DirectedEdge(Node<N> * v, const double & w = 0);

    //ACCESSORS
    N getOtherNodeID() const;
    Node<N> getOtherNode() const;

private:
    node_ptr<N> p;

};

//MULTIGRAPH EDGE
template <class N = string>
class Multi : public Edge<N> {
public:
    //CONSTRUCTORS
    Multi(Node<N> * v, const int & count = 1);

    //ACCESSORS
    int getMultiSize() const;
    N getOtherNodeID() const;
    Node<N> getOtherNode() const;

    //MUTATORS
    void setAllWeight(const double & w);
    void setOneWeight(const int & i, const double & w);

private:
    vector<pair<node_ptr<N>, double>> edges;

};
#endif
