#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Graph {
public:
    vector<pair<int, pair<int, int>>> edges;//matrix of edges

    void addEdge(int v1, int v2, int weight) {
        edges.push_back({ weight, {v1, v2} }); // Adding edge to the graph
    }
};

class DisjointSet {
private:
    int* parent;
    int* rank;
    int size;

public:
    DisjointSet(int vertices) {
        size = vertices;
        parent = new int[vertices];
        rank = new int[vertices];
        for (int i = 0; i < vertices; i++)
            makeSet(i); // Making set for each vertex
    }

    

    int findSet(int v) {
        if (v != parent[v])
            parent[v] = findSet(parent[v]); // Path compression
        return parent[v];
    }

    void unionSets(int v1, int v2) {
        int root1 = findSet(v1);
        int root2 = findSet(v2);

        if (root1 != root2) {
            if (rank[root1] < rank[root2])
                parent[root1] = root2;
            else if (rank[root1] > rank[root2])
                parent[root2] = root1;
            else {
                parent[root2] = root1;
                rank[root1]++;
            }
        }
    }
    void makeSet(int v) {
        parent[v] = v; // Initializing parent as itself
        rank[v] = 0; // Initializing rank as 0
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }
};

class MSTKruskal {
private:
    DisjointSet ds;

    void quickSort(vector<pair<int, pair<int, int>>>& arr, int low, int high) {
        if (low < high) {
            int pivot = arr[high].first;
            int i = low - 1;
            for (int j = low; j <= high - 1; j++) {
                if (arr[j].first < pivot) {
                    i++;
                    swap(arr[i], arr[j]);
                }
            }
            swap(arr[i + 1], arr[high]);
            int pivotIndex = i + 1;
            quickSort(arr, low, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, high);
        }
    }

public:
    MSTKruskal(int vertices) : ds(vertices) {}

    void findMST(Graph& graph, int size) {
        quickSort(graph.edges, 0, size - 1); // Sorting edges by weight

        int totalWeight = 0;
        int count = 0, i = 0;
        while (count < size - 1) {
            int v1 = graph.edges[i].second.first;
            int v2 = graph.edges[i].second.second;
            int weight = graph.edges[i].first;

            if (ds.findSet(v1) != ds.findSet(v2)) { // If including this edge does not form a cycle
                cout << "Vertex \"" << v1 << "\" -- > Vertex \"" << v2 << "\" : " << weight << endl; // Printing edge of MST
                totalWeight += weight;
                count++;
                ds.unionSets(v1, v2); // Merging the sets of v1 and v2
            }
            i++;
        }
        cout << "\nTotal weight of MST: " << totalWeight << endl;
    }
};
