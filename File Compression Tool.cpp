#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

// Comparison object for priority queue
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Traverse the Huffman Tree and build the encoding map
void buildEncodingMap(Node* root, const string& str, unordered_map<char, string>& huffmanCode) {
    if (!root)
        return;

    // Leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    buildEncodingMap(root->left, str + "0", huffmanCode);
    buildEncodingMap(root->right, str + "1", huffmanCode);
}

// Free the allocated memory for the Huffman Tree
void freeTree(Node* root) {
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Perform Huffman encoding
void huffmanCompress(const string& inputFile, const string& outputFile) {
    // Step 1: Read the input file and calculate frequency of each character
    ifstream input(inputFile, ios::binary);
    if (!input) {
        cerr << "Error: Could not open input file." << endl;
        return;
    }

    unordered_map<char, int> freq;
    char ch;
    while (input.get(ch)) {
        freq[ch]++;
    }
    input.clear();
    input.seekg(0);

    // Step 2: Build the Huffman Tree
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }

    Node* root = pq.top();

    // Step 3: Build the encoding map
    unordered_map<char, string> huffmanCode;
    buildEncodingMap(root, "", huffmanCode);

    // Step 4: Write the encoded data to the output file
    ofstream output(outputFile, ios::binary);
    if (!output) {
        cerr << "Error: Could not open output file." << endl;
        freeTree(root);
        return;
    }

    // Write the encoding map size
    size_t mapSize = huffmanCode.size();
    output.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

    // Write the encoding map
    for (const auto& pair : huffmanCode) {
        output.put(pair.first);
        size_t codeSize = pair.second.size();
        output.write(reinterpret_cast<const char*>(&codeSize), sizeof(codeSize));
        output.write(pair.second.c_str(), codeSize);
    }

    // Write the encoded content
    string encodedStr;
    while (input.get(ch)) {
        encodedStr += huffmanCode[ch];
    }

    // Pad the encoded string to make it byte-aligned
    int padding = 8 - (encodedStr.size() % 8);
    for (int i = 0; i < padding; ++i) {
        encodedStr += '0';
    }

    output.put(static_cast<char>(padding));

    for (size_t i = 0; i < encodedStr.size(); i += 8) {
        bitset<8> byte(encodedStr.substr(i, 8));
        output.put(static_cast<char>(byte.to_ulong()));
    }

    input.close();
    output.close();

    // Free memory
    freeTree(root);

    cout << "File successfully compressed to " << outputFile << endl;
}

int main() {
    string inputFile, outputFile;
    cout << "Enter the name of the input file: ";
    cin >> inputFile;
    cout << "Enter the name of the output file: ";
    cin >> outputFile;

    huffmanCompress(inputFile, outputFile);

    return 0;
}
