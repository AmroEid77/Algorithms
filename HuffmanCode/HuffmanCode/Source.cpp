#include "iostream"
#include "string"
#include"HuffmanCode.h"
using namespace std;

int main() {
    string paragraph;
    cout << "Please provide the text paragraph : ";
    getline(cin, paragraph);

    HuffmanCode huffman(paragraph);

    //Print character with their counts
    huffman.printCharWithCounts();
    
    // Print Huffman codes
    cout << "\nHuffman Codes(in Binary):\n";
    huffman.printHuffmanCodes();

    // Encode text
    string encodedText = huffman.encodeText(paragraph);
    cout << "\nEncoded Text: " << encodedText << endl;

    // Decode text
    string decodedText = huffman.decodeText(encodedText);
    cout << "\nDecoded Text: " << decodedText << endl;

    // Calculate total bits needed to encode the paragraph
    cout << "\nTotal bits needed to encode the paragraph: " << huffman.totalBits(paragraph) << endl;

    
    //Read a string and print its binary code using Huffman codes
    string inputString;
    cout << "\nPlease Enter the string to encode: ";
    getline(cin, inputString);
    string encodedString = huffman.encodeText(inputString);
    cout << "Binary code for the input string: " << encodedString << endl;

    // Read a sequence of binary code and print out the corresponding characters
    string binarySequence;
    cout << "\nEnter a binary sequence to decode: ";
    getline(cin, binarySequence);
    string decodedSequence = huffman.decodeText(binarySequence);
    cout << "Decoded sequence: " << decodedSequence << endl;

}
