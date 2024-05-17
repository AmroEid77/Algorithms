#include <iostream>
#include "Graph.h"

using namespace std;



int main() {
    // Define the adjacency matrix
    vector<vector<int>> matrix= {
        {0, 80, 90, 150},
        {41, 0, 65, 23},
        {77, 8, 0, 2},
        {54, 54, 80, 0}
    };
    //Graph graph(matrix);
    
    
    //Create a graph object 5 x 5
    Graph graph(4);
    graph.addRow({ 0, 10, 15, 20 });
    graph.addRow({ 5, 0, 9, 10 });
    graph.addRow({ 6, 13, 0, 12 });
    graph.addRow({ 8, 8, 9, 0 });
    graph.addRow({ 8, 8, 9, 0 });
    

    // Print the adjacency matrix
    graph.printAdjacencyMatrix();
    graph.reduceRow();
    graph.printAdjacencyMatrix("row");
    graph.reduceColumn();
    graph.printAdjacencyMatrix("colmun");



    return 0;

}
