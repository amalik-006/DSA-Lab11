#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;
};

struct MinHeap {
    Node* arr[100];  // arr[] to store pointers to nodes
    int size;
};

// Create a new node
Node* createNode(char data, int frequency) {

    Node* newNode = new Node;

    newNode->data = data;
    newNode->frequency = frequency;
    newNode->left = newNode->right = nullptr;

    return newNode;
}

void swapElements(MinHeap* heap, int i) {
    int smallest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // swap with left child
    if (left < heap->size && heap->arr[left]->frequency < heap->arr[smallest]->frequency) {
        smallest = left;
    }

    // swap with right child
    if (right < heap->size && heap->arr[right]->frequency < heap->arr[smallest]->frequency) {
        smallest = right;
    }

    if (smallest != i) {
        Node* temp = heap->arr[i];
        heap->arr[i] = heap->arr[smallest];
        heap->arr[smallest] = temp;

        swapElements(heap, smallest);
    }
}

// Insert into Min Heap
void insertHeap(MinHeap* heap, Node* newNode) {
    int i = heap->size;

    heap->arr[i] = newNode;
    heap->size++;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap->arr[parent]->frequency <= heap->arr[i]->frequency) {
            break;
        }

        Node* temp = heap->arr[i];
        heap->arr[i] = heap->arr[parent];
        heap->arr[parent] = temp;

        i = parent;
    }
}

// Extracting minimum value
Node* extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        return nullptr;
    }

    Node* minNode = heap->arr[0];

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    if (heap->size > 0) {
        swapElements(heap, 0);
    }
    return minNode;
}

// Create initial Min Heap
MinHeap* createMinHeap(char S[], int f[], int N) {
    MinHeap* heap = new MinHeap;
    heap->size = 0;

    for (int i = 0; i < N; i++) {
        Node* newNode = createNode(S[i], f[i]);
        insertHeap(heap, newNode);
    }
    return heap;
}

// Build Huffman Tree
Node* buildHuffmanTree(char S[], int f[], int N) {
    MinHeap* heap = createMinHeap(S, f, N);

    while (heap->size > 1) {
        Node* left = extractMin(heap);
        Node* right = extractMin(heap);
        Node* parent = createNode('\0', left->frequency + right->frequency);

        parent->left = left;
        parent->right = right;

        insertHeap(heap, parent);
    }
    return extractMin(heap);
}

// Preorder traversal
void preorder(Node* root, string code) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        cout << root->data << ": " << code << endl;
        return;
    }

    preorder(root->left, code + "0");
    preorder(root->right, code + "1");
}

// Main
int main() {
    int N;

    cout << "Enter number of distinct characters: ";
    cin >> N;

    char* S = new char[N];
    int* f = new int[N];

    cout << "Enter characters:\n";
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    cout << "Enter corresponding frequencies:\n";
    for (int i = 0; i < N; i++) {
        cin >> f[i];
    }

    Node* root = buildHuffmanTree(S, f, N);

    cout << "\nHuffman Codes:\n";

    preorder(root, "");

    delete[] S;
    delete[] f;

    return 0;
}