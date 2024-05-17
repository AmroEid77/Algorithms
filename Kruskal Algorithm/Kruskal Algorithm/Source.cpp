#include "iostream"
#include "Kruskal.h" 
using namespace std;

int main() {
    int numVertices;
    cout << "Enter the number of Vertices: ";
    cin >> numVertices;
    Graph graph;
    // add values (src , des , wieght) based index 0
    //my own example
    graph.addEdge(0, 1, 10); // Adding an edge from vertex 0 to vertex 1 with weight 10
    graph.addEdge(0, 2, 7); // Adding an edge from vertex 0 to vertex 2 with weight 7
    graph.addEdge(1, 2, 9); // Adding an edge from vertex 1 to vertex 2 with weight 9
    graph.addEdge(2, 3, 32); // Adding an edge from vertex 2 to vertex 3 with weight 32
    graph.addEdge(2, 4, 23); // Adding an edge from vertex 2 to vertex 4 with weight 23

    cout << endl << "The Minimum Spanning Tree (MST) using Kruskal's algorithm\n";
    MSTKruskal mst(numVertices); // Creating a object of MSTKruskal class
    mst.findMST(graph, numVertices); // Finding the Minimum Spanning Tree (MST) using Kruskal's algorithm
}
