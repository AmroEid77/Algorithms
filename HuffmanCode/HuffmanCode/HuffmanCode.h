#pragma once
#include "iostream"
#include "string"
#include "map"
#include "queue"

using namespace std;

// Class for a node in the Huffman tree
class HuffmanNode {
public:
    char data; // Character
    int recurrence; // recurrence of the character
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int recurrence) {
        this->data = data;
        this->recurrence = recurrence;
        left = NULL;
        right = NULL;
    }
};

// Comparison for priority queue
class CompareNodes {
public:
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->recurrence > right->recurrence;
    }
};

class HuffmanCode {
private:
    // Private member variables
    map<char, string> huffmanCodes;
    HuffmanNode* root;
    int charCounts[256] = { 0 }; // Array to store character frequencies

    // Function to build Huffman Tree and return the root
    HuffmanNode* buildHuffmanTree(const map<char, int>& freqMap) {
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

        // Create leaf nodes for each character and add them to the priority queue
        for (const auto& pair : freqMap) {
            minHeap.push(new HuffmanNode(pair.first, pair.second));
        }

        // Build Huffman Tree
        while (minHeap.size() > 1) {
            HuffmanNode* left = minHeap.top();
            minHeap.pop();
            HuffmanNode* right = minHeap.top();
            minHeap.pop();

            HuffmanNode* parent = new HuffmanNode('\0', left->recurrence + right->recurrence);
            parent->left = left;
            parent->right = right;

            minHeap.push(parent);
        }

        return minHeap.top();
    }

    // Function to generate Huffman codes
    void generateHuffmanCodes(HuffmanNode* root, const string& prefix) {
        if (root == NULL)
            return;

        if (root->left == NULL && root->right == NULL) {
            huffmanCodes[root->data] = prefix;
            return;
        }

        generateHuffmanCodes(root->left, prefix + "0");
        generateHuffmanCodes(root->right, prefix + "1");
    }

public:
    // Constructor
    HuffmanCode(const string& text) {
        // Count occurrences of each character and save in charCounts array
        for (char c : text) {
            charCounts[c]++;
        }

        //Build Huffman Tree
        map<char, int> freqMap;
        for (int i = 0; i < 256; ++i) {
            if (charCounts[i] > 0) {
                freqMap[i] = charCounts[i];
            }
        }
        root = buildHuffmanTree(freqMap);

        //Generate Huffman codes
        generateHuffmanCodes(root, "");
    }

    void printCharWithCounts() {
        // Print character counts
        cout << "Character Counts:\n";
        for (int i = 0; i < 256; ++i) {
            if (charCounts[i] > 0) {
                cout << "'" << (char)i << "': " << charCounts[i] << endl;
            }
        }
    }

    // Function to encode text using Huffman codes
    string encodeText(const string& text) const {
        string encodedText = "";
        for (char c : text) {
            encodedText += huffmanCodes.at(c);
        }
        return encodedText;
    }

    // Function to decode text using Huffman tree
    string decodeText(const string& encodedText) const {
        string decodedText = "";
        HuffmanNode* current = root;
        for (char bit : encodedText) {
            if (bit == '0') {
                current = current->left;
            }
            else {
                current = current->right;
            }
            if (current->left == NULL && current->right == NULL) {
                decodedText += current->data;
                current = root;
            }
        }
        return decodedText;
    }

    // Function to get Huffman codes
    void printHuffmanCodes() const {
        for (const auto& pair : huffmanCodes) {
            cout << "'" << pair.first << "': " << pair.second << endl;
        }
    }

    // Function to calculate total bits needed to encode the text
    int totalBits(const string& text) const {
        return encodeText(text).size();
    }
};