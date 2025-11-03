//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"

using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    cout << "Entering buildEncodingTree with nextFree=" << nextFree << endl;

    // 1. Create a MinHeap object.
    MinHeap heap;

    // 2. Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; ++i) {
        cout << "Pushing " << i << " weight=" << weightArr[i] << endl;
        if (weightArr[i] > 0) {
            heap.push(i, weightArr);
        }
    }

    cout << "Finished pushing. Heap size=" << heap.size << endl;


    // handles empty input
    if (heap.size == 0) {
        return -1;
    }

    // if only one node, we know it's the root
    if (heap.size == 1) {
        return heap.pop(weightArr);
    }

    // 3. While the heap size is greater than 1:
    while (heap.size > 1) {
        //    - Pop two smallest nodes
        int idx1 = heap.pop(weightArr);
        int idx2 = heap.pop(weightArr);

        if (idx1 == -1 || idx2 == -1) {
            cout << "Heap is empty, nothing to remove.\n";
            return -1;
        }

        //    - Create a new parent node with combined weight
        //    - Set left/right pointers
        int parent = nextFree++;

        if (nextFree >= MAX_NODES) {
            cout << "Node array overflow";
            return -1;
        }

        weightArr[parent] = weightArr[idx1] + weightArr[idx2];
        charArr[parent] = '\0';  // internal node
        if (weightArr[idx2] < weightArr[idx1]) swap(idx1, idx2);
        leftArr[parent] = idx1;  // first popped --> left
        rightArr[parent] = idx2; // second popped --> right

        //    - Push new parent index back into the heap
        heap.push(parent, weightArr);
    }

    // 4. Return the index of the last remaining node (root)
    int root = heap.pop(weightArr);

    return root;
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    for (int i = 0; i < 26; ++i) codes[i].clear();

    if (root == -1) return;

    struct Frame {
        int idx;
        string code;
    };

    stack<Frame> stack;
    stack.push({root, ""});

    while (!stack.empty()) {
        Frame f = stack.top();
        stack.pop();

        int idx = f.idx;
        string cur = f.code;

        if (leftArr[idx] == -1 && rightArr[idx] == -1) {
            if (charArr[idx] >= 'a' && charArr[idx] <= 'z') {
                char c = charArr[idx];

                if (cur.empty()) cur = "0";
                codes[c - 'a'] = cur;
            }
            continue;
        }

        if (rightArr[idx] != -1) {
            stack.push({ rightArr[idx], cur + "1" });
        }

        if (leftArr[idx] != -1) {
            stack.push({ leftArr[idx], cur + "0"});
        }
    }

}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}