#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

// Directed Acyclic Graph (DAG)
template<typename T>
class Graph {
private:
    // Map to store vertices with Indices ( key : value ) same dict in python
    map<T, int> vertexIndices;

    // A vector of list to represent an adjacency list "vertcies and thier edges )
    //(private data member )
    vector<list<int>> adjList;

    //vector for storing in-degree of the vertices 
    //(private data member )
    vector<int> indegree;

    // print all possible paths
    void printPath(list<T> list) {
        while (!list.empty()) {
            cout << list.front() << ' ';
            list.pop_front();
        }
        cout << endl;
    }

    // Recursive function to find all topological ordering of a given DAG
    void findAllTopologicalOrderings(list<T>& path, vector<bool>& isVisited, int n) {
        //for every vertex in graph
        for (int v = 0; v < n; v++) {
            // only if the current vertex in-degree is 0 and not visited
            if (indegree[v] == 0 && !isVisited[v]) {
                //decrease in-degree of connectedVertex
                if(v<adjList.size())
                for (int connectedVertex : adjList[v]) {
                    indegree[connectedVertex]--;
                }

                // add the current vertex in the path and mark itVisited
                path.push_back(getKey(v));
                isVisited[v] = true;

                // Recursive call (using system stack)
                findAllTopologicalOrderings(path, isVisited, n);

                // backtrack: reset in-degree for the current vertex after system stack called
                if (v < adjList.size())
                for (int connectedVertex : adjList[v]) {
                    indegree[connectedVertex]++;
                }

                // backtrack: remove the current vertex from the path
                // mark it as unVisited
                path.pop_back();
                isVisited[v] = false;
            }
        }

        // print the topological order if all vertices are included in the path
        if (path.size() == n) {
            printPath(path);
        }
    }

public:
    //Constructor
    Graph() {}
    // Member function to add an edge to the graph
    void addEdge(T source, T destination) {
        // Add the source vertex if it doesn't exist
        if (!vertexIndices.count(source)) {
            vertexIndices[source] = vertexIndices.size();
            indegree.push_back(0);
        }

        // Add the destination vertex if it doesn't exist
        if (!vertexIndices.count(destination)) {
            
            vertexIndices[destination] = vertexIndices.size();
            indegree.push_back(0);

        }

        // Get the indices of source and destination vertices
        int srcIndex = vertexIndices[source];
        int destIndex = vertexIndices[destination];

        // Resize the adjacency list if necessary
        
        if (adjList.size() <= srcIndex) {
            adjList.resize(srcIndex + 1);
            
        }

        // Add the destination index to the adjacency list of the source vertex
        adjList[srcIndex].push_back(destIndex);

        // Increment in-degree of destination vertex by 1
        indegree[destIndex]++;
    }

    // Print all topological orderings of DAG
    void printAllTopologicalOrders() {
        //number of vertex
        int n = indegree.size();

        // vector to check if the node (vertex) is visited or not  (by default vectro fill by 0 mean false )
        vector<bool> isVisited(n);

        // list to store the topological order
        list<T> path;

        // find all topological ordering and print them
        findAllTopologicalOrderings(path, isVisited, n);
    }
    void printAdjList() const {
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Vertex " << getKey(i) << " has edges to: ";
            for (int index : adjList[i]) {
                cout << getKey(index) << " ";
            }
            cout << endl;
        }
        cout << endl << "Number of vertices in the graph is :" << size() << endl << endl;

    }

    T getKey(int index) const {
        for (const auto& pair : vertexIndices) {
            if (pair.second == index) {
                return pair.first;
            }
        }
    }
    int size()const {
        return indegree.size();
    }
};