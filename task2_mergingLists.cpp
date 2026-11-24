#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct MinHeap {
    Node** arr;  // every heap element is a pointer to a linked-list node
    int size;
    int capacity;
};

// Create Node
Node* createNode(int data) {
    Node* newNode = new Node;

    newNode->data = data;
    newNode->next = nullptr;

    return  newNode;
}

// Create Linked List
Node* createList(int n) {
    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; i++){
        int value;
        cin >> value;

        Node* newNode = createNode(value);

        if (head == nullptr){
            head = tail = newNode;
        }else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Swap Elements
void swapElements(MinHeap* heap, int i) {
    int smallest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // swap with left child
    if (left < heap->size && heap->arr[left]->data < heap->arr[smallest]->data) {
        smallest = left;
    }

    // swap with right child
    if (right < heap->size && heap->arr[right]->data < heap->arr[smallest]->data) {
        smallest = right;
    }

    if (smallest != i) {
        Node* temp = heap->arr[i];
        heap->arr[i] = heap->arr[smallest];
        heap->arr[smallest] = temp;

        swapElements(heap, smallest);
    }
}

// Insert into Heap
void insertHeap(MinHeap* heap, Node* newNode) {
    int i = heap->size;

    heap->arr[i] = newNode;
    heap->size++;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap->arr[parent]->data <= heap->arr[i]->data) {
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

// Creating Min Heap
MinHeap* createMinHeap(Node* lists[], int k) {
    MinHeap* heap = new MinHeap;

    heap->arr = new Node*[k];
    heap->size = 0;
    heap->capacity = k;

    for (int i = 0; i < k; i++) {
        if (lists[i] != nullptr) {
            insertHeap(heap, lists[i]);
        }
    }
    return heap;
}

// Merging Lists
Node* mergeKLists(Node* lists[], int k) {
    MinHeap* heap = createMinHeap(lists, k);

    Node* head = nullptr;
    Node* tail = nullptr;

    while (heap->size > 0) {
        Node* minNode = extractMin(heap);
        if (head == nullptr) {
            head = tail = minNode;
        }
        else {
            tail->next = minNode;
            tail = minNode;
        }

        if (minNode->next != nullptr) {
            insertHeap(heap, minNode->next);
        }
    }

    if (tail != nullptr) {
        tail->next = nullptr;
    }

    delete[] heap->arr;
    delete heap;

    return head;
}

void display(Node* head) {
    while (head != nullptr) {
        cout << head->data;

        if (head->next != nullptr) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << endl;
}

// Main
int main() {
    int k;

    cout << "Enter number of linked lists: ";
    cin >> k;

    if (k <= 0) {
        cout << "Invalid number of lists\n";
        return 0;
    }

    Node** lists = new Node*[k];

    for (int i = 0; i < k; i++) {
        int n;

        cout << "Enter number of nodes in list " << i + 1 << ": ";
        cin >> n;

        if (n < 0) {
            cout << "Invalid list size\n";
            return 1;
        }
        cout << "Enter sorted elements: ";
        lists[i] = createList(n);
    }

    Node* merged = mergeKLists(lists, k);

    cout << "\nMerged Linked List:\n";
    display(merged);

    // Free memory
    while (merged != nullptr) {
        Node* temp = merged;
        merged = merged->next;

        delete temp;
    }
    delete[] lists;

    return 0;
}