#include "iostream"
#include "Graph.h"

using namespace std;

int main() {
    Graph<char> graph;

    // add edges to the graph
    graph.addEdge('a', 'b');
    graph.addEdge('a', 'c');
    graph.addEdge('c', 'd');

    /* example DAG
        a-->b
         \
          c-->d
    so the output would be 
    a b c d
    a c b d
    a c d b
    */
    // print each vertex and thier edges
    graph.printAdjList();
    cout << "Print all possible topological ordering of the graph ( DAG )" << endl;
    graph.printAllTopologicalOrders();
    

    return 0;
}
