#pragma once

#include <iomanip> 
#include <vector>

using namespace std;
class Graph {
private:
    int** adjacency_matrix;
    int size;
    int currentRows;
    int sumDiffernece;

public:
    Graph(int size) : sumDiffernece(0), currentRows(0) {
        this->size = size;
        // Allocate memory for the adjacency matrix
        adjacency_matrix = new int* [size];
        for (int i = 0; i < size; i++) {
            adjacency_matrix[i] = new int[size] {0};
        }
    }
    Graph(const vector<vector<int>>& matrix) :size(matrix.size()), sumDiffernece(0), currentRows(size) {


        // Allocate memory for the adjacency matrix
        adjacency_matrix = new int* [size];
        for (int i = 0; i < size; i++) {
            adjacency_matrix[i] = new int[size];
            for (int j = 0; j < size; j++) {
                adjacency_matrix[i][j] = matrix[i][j];
            }
        }
    }

    void addRow(const vector<int>& row) {
        if (row.size() > size) {
            cout << "you excede the size of the row which is " << size << " and you enter " << row.size() << endl;
            exit(1);
        }

        else if (currentRows >= size) {
            cout << "the matrix is full you can't add more\n";
            return;
        }
        else {
            for (int i = 0; i < size; i++) {
                adjacency_matrix[currentRows][i] = row[i];
            }
            currentRows++;
        }
    }

    int min(int index, const string& type = "") {
        int minValue = INT_MAX;
        int zeroCheck = 0;

        if (type == "col") {
            for (int i = 0; i < currentRows; i++) {
                if (adjacency_matrix[i][index] == 0) {
                    zeroCheck++;
                }
                if (adjacency_matrix[i][index] != 0 && adjacency_matrix[i][index] < minValue) {
                    minValue = adjacency_matrix[i][index];
                }
            }
            return (zeroCheck >= currentRows - 1) ? 0 : minValue;
        }
        else if (type == "row") {
            for (int i = 0; i < currentRows; i++) {
                if (adjacency_matrix[index][i] == 0) {
                    zeroCheck++;
                }
                if (adjacency_matrix[index][i] != 0 && adjacency_matrix[index][i] < minValue) {
                    minValue = adjacency_matrix[index][i];
                }
            }
            return (zeroCheck >= currentRows - 1) ? 0 : minValue;
        }
        else {
            return 0;
        }

    }

    void printAdjacencyMatrix(const string& message = "") {
        cout << "--------------------------------------------------\n";
        if (message == "") {
            cout << "Adjacency Matrix before reduction:" << endl;
        }
        else
            cout << "Adjacency Matrix after " << message << " reduction:" << endl;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << setw(5) << adjacency_matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Sum Difference: " << sumDiffernece << endl;
        cout << "--------------------------------------------------\n";
    }
    void reduceRow() {

        for (int i = 0; i < currentRows; i++) {
            int minValue = min(i, "row");
            for (int j = 0; j < currentRows; j++) {
                if (adjacency_matrix[i][j] != 0) {
                    adjacency_matrix[i][j] -= minValue;

                }
            }
            sumDiffernece += minValue;

        }
    }

    void reduceColumn() {


        for (int i = 0; i < currentRows; i++) {
            int minValue = min(i, "col");
            for (int j = 0; j < currentRows; j++) {
                if (adjacency_matrix[j][i] != 0) {
                    adjacency_matrix[j][i] -= minValue;

                }
            }
            sumDiffernece += minValue;
        }
    }

    ~Graph() {
        // Deallocate memory for the adjacency matrix
        for (int i = 0; i < currentRows; i++) {
            delete[] adjacency_matrix[i];
        }
        delete[] adjacency_matrix;
    }
};