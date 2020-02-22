#include <algorithm>
#include <tuple>
#include "Graph.h"
using namespace std;

//D I J K S T R A ' S      A L G O R I T H M
// template <class G, class N>
// vector<Node<N>> dijkstras(const Graph<G, N> & g) {
//     using entry = tuple<bool, double, double>;
//     vector<vector<entry>> distMatrix(g.getSize(), g.getSize(), inf);
// }

//FLEURY ALGORITHM
template <class G, class N>
vector<pair<N, N>> fleuryCircuit(const Graph<G, N> & g) {
    vector<pair<N,N>> edges;
    //for(unsigned int i = 1; i <= g.setSize(); i++)
    if(count_if(g.V.begin(), g.V.end(), [](Node<N> n){return n.getDegree() % 2 == 1;}) != 0 &&
        count_if(g.V.begin(), g.V.end(), [](Node<N> n){return n.getDegree() % 2 == 1;}) != 2)
        return edges;

    Node<N> current = g.V.front();
    while(current.getDegree() > 0) {
        edges.push_back({current.getID(), current.links.front() -> getOtherNodeID()});
        current.deleteNode(1); 


    }


    //error checking
    // if(edges.size() != g.getEdgeSize()){
    //     edges.clear();
    //     return edges;
    // } else
    //     return edges;
}

// template <class G, class N>
// vector<N> fleuryPath(const Graph<G, N> & g)
