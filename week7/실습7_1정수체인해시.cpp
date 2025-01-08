#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Node class for hash table entries
class Node {
public:
    int key;             // Key value
    Node* next;          // Pointer to the next node in the chain

    // Constructors
    Node(int key) : key(key), next(nullptr) {}
    Node(int key, Node* p) : key(key), next(p) {}

    int getKey() {
        return key;
    }
};

class SimpleChainHash {
private:
    int size;              // Hash table size
    vector<Node*> table;   // Hash table as a vector of Node pointers

public:
    // Constructor
    SimpleChainHash(int capacity) : size(capacity) {
        table.resize(size, nullptr);
    }

    // Hash function
    int hashValue(int key) {
        int hash = 11;
        hash = 31 * hash * key;
        hash = hash * hash;
        return hash;
    }

    // Search for a key
    int search(int key) {
    
        return 0;  // Search failure
    }

    // Add a key to the hash table
    int add(int key) {
  
        return 1;
    }

    // Delete a key from the hash table
    int deleteKey(int key) {
        int hash = hashValue(key) % 10;
        Node* p = table[hash];
        Node* pp = nullptr;

        while (p != nullptr) {
    
        return 0;  // Key not found
    }

    // Display the hash table contents
    void dump() {
        for (int i = 0; i < size; i++) {

        }
    }
};

// Enum for menu options
enum Menu {
    Add = 1, Delete, Search, Show, Exit
};

// Menu selection function
Menu SelectMenu() {
    int key;
    do {
        cout << "(1) Add  (2) Delete  (3) Search  (4) Show  (5) Exit: ";
        cin >> key;
    } while (key < Add || key > Exit);
    return static_cast<Menu>(key);
}

int main() {
    SimpleChainHash hash(11);
    int result = 0, val = 0;
    const int count = 15;
    srand(time(0));

    Menu menu;
    do {
        menu = SelectMenu();
        switch (menu) {
        case Add: {
            int input[count];
            for (int i = 0; i < count; i++) {
                input[i] = rand() % 20;
                cout << " " << input[i];
            }
            cout << endl;

            for (int i = 0; i < count; i++) {
                if (hash.add(input[i]) == 0)
                    cout << "Insert Duplicated data" << endl;
            }
            break;
        }
        case Delete:
            cout << "Delete Value: ";
            cin >> val;
            result = hash.deleteKey(val);
            if (result == 1)
                cout << "Data deleted successfully." << endl;
            else
                cout << "Data not found." << endl;
            break;
        case Search:
            cout << "Search Value: ";
            cin >> val;
            result = hash.search(val);
            if (result == 1)
                cout << "Data found." << endl;
            else
                cout << "Data not found." << endl;
            break;
        case Show:
            hash.dump();
            break;
        case Exit:
            cout << "Exiting program." << endl;
            break;
        }
    } while (menu != Exit);

    return 0;
}
