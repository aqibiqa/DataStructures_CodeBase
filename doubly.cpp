#include <iostream>
using namespace std;

/* ===============================================================
    CLASS: DNode
    ----------------------------------------------------------------
    Each DNode object represents a single element (node) in the
    doubly linked list. It contains three important pieces of data:
     1. An integer 'value' that stores the actual data.
     2. A pointer 'next_node' to the next node in the list.
     3. A pointer 'prev_node' to the previous node in the list.
==================================================================*/
class DNode {
private:
    int value;
    DNode* next_node;
    DNode* prev_node;

public:
    /* ------------------------------------------------------------
        CONSTRUCTOR: DNode
        ------------------------------------------------------------
        Creates a new node. By default, its value is 0 and
        its next/prev pointers are null.
    -------------------------------------------------------------*/
    DNode(int val = 0, DNode* next = nullptr, DNode* prev = nullptr)
        : value(val), next_node(next), prev_node(prev) {}

    /* ------------------------------------------------------------
        ACCESSOR: int retrieve() const
        ------------------------------------------------------------
        Returns the data value stored in the current node.
    -------------------------------------------------------------*/
    int retrieve() const { return value; }

    /* ------------------------------------------------------------
        ACCESSOR: DNode* next() const
        ------------------------------------------------------------
        Returns the address of the next node.
    -------------------------------------------------------------*/
    DNode* next() const { return next_node; }

    /* ------------------------------------------------------------
        ACCESSOR: DNode* prev() const
        ------------------------------------------------------------
        Returns the address of the previous node.
    -------------------------------------------------------------*/
    DNode* prev() const { return prev_node; }

    /* ------------------------------------------------------------
        MUTATOR: void set_next(DNode* next)
        ------------------------------------------------------------
        Updates the 'next_node' pointer of this node.
    -------------------------------------------------------------*/
    void set_next(DNode* next) { next_node = next; }

    /* ------------------------------------------------------------
        MUTATOR: void set_prev(DNode* prev)
        ------------------------------------------------------------
        Updates the 'prev_node' pointer of this node.
    -------------------------------------------------------------*/
    void set_prev(DNode* prev) { prev_node = prev; }

    // Friend class declaration
    friend class DList;
};

/* ===============================================================
    CLASS: DList
    ----------------------------------------------------------------
    The DList class represents a doubly linked list. It manages
    the collection of DNode objects using two pointers:
     1. 'list_head' points to the first node (head).
     2. 'list_tail' points to the last node (tail).
==================================================================*/
class DList {
private:
    DNode* list_head;
    DNode* list_tail;

public:
    /* ------------------------------------------------------------
        CONSTRUCTOR: DList()
        ------------------------------------------------------------
        Initializes the list to an empty state. Both head and
        tail are set to nullptr.
    -------------------------------------------------------------*/
    DList() : list_head(nullptr), list_tail(nullptr) {}

    /* ------------------------------------------------------------
        DESTRUCTOR: ~DList()
        ------------------------------------------------------------
        Ensures all dynamically allocated memory is freed by
        repeatedly calling pop_front() until the list is empty.
    -------------------------------------------------------------*/
    ~DList() {
        while (!empty())
            pop_front();
    }

    /* ------------------------------------------------------------
        FUNCTION: bool empty() const
        ------------------------------------------------------------
        Checks if the list has any nodes.
        Returns true if list_head is nullptr, otherwise false.
    -------------------------------------------------------------*/
    bool empty() const {
        return (list_head == nullptr);
    }

    /* ------------------------------------------------------------
        FUNCTION: int size() const
        ------------------------------------------------------------
        Traverses the list from head to tail and counts the nodes.
    -------------------------------------------------------------*/
    int size() const {
        int count = 0;
        for (DNode* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            ++count;
        return count;
    }

    /* ------------------------------------------------------------
        FUNCTION: int front() const
        ------------------------------------------------------------
        Returns the data value of the first node (head).
    -------------------------------------------------------------*/
    int front() const {
        if (empty()) {
            cerr << "List is empty! Cannot access front element.\n";
            return -1;
        }
        return list_head->retrieve();
    }

    /* ------------------------------------------------------------
        FUNCTION: int end() const
        ------------------------------------------------------------
        Returns the data value of the last node (tail).
    -------------------------------------------------------------*/
    int end() const {
        if (empty()) {
            cerr << "List is empty! Cannot access end element.\n";
            return -1;
        }
        return list_tail->retrieve();
    }

    /* ------------------------------------------------------------
        FUNCTION: DNode* head() const
        ------------------------------------------------------------
        Returns the head pointer (address of the first node).
    -------------------------------------------------------------*/
    DNode* head() const {
        return list_head;
    }

    /* ------------------------------------------------------------
        FUNCTION: DNode* tail() const
        ------------------------------------------------------------
        Returns the tail pointer (address of the last node).
    -------------------------------------------------------------*/
    DNode* tail() const {
        return list_tail;
    }

    /* ------------------------------------------------------------
        FUNCTION: int count(int n) const
        ------------------------------------------------------------
        Counts how many nodes contain the specified integer value 'n'.
    -------------------------------------------------------------*/
    int count(int n) const {
        int node_count = 0;
        for (DNode* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            if (ptr->retrieve() == n)
                ++node_count;
        }
        return node_count;
    }

    /* ------------------------------------------------------------
        FUNCTION: void push_front(int n)
        ------------------------------------------------------------
        Inserts a new node 'n' at the beginning of the list.
        Must update head, and potentially tail (if list was empty).
    -------------------------------------------------------------*/
    void push_front(int n) {
        DNode* new_node = new DNode(n, list_head, nullptr);

        if (empty()) {
            // Case 1: List is empty
            list_head = list_tail = new_node;
        } else {
            // Case 2: List is not empty
            list_head->set_prev(new_node);
            list_head = new_node;
        }
    }

    /* ------------------------------------------------------------
        FUNCTION: void push_end(int n)
        ------------------------------------------------------------
        Adds a new node 'n' to the end of the list.
        Must update tail, and potentially head (if list was empty).
    -------------------------------------------------------------*/
    void push_end(int n) {
        DNode* new_node = new DNode(n, nullptr, list_tail);

        if (empty()) {
            // Case 1: List is empty
            list_head = list_tail = new_node;
        } else {
            // Case 2: List is not empty
            list_tail->set_next(new_node);
            list_tail = new_node;
        }
    }

    /* ------------------------------------------------------------
        FUNCTION: void push_between(int index, int n)
        ------------------------------------------------------------
        Inserts a new node with value 'n' at the specified index.
        Index 0 inserts before the first node (same as push_front).
        If index equals the list size, it appends (same as push_end).
        For indices in between, inserts after the node at index-1.
    -------------------------------------------------------------*/
    void push_between(int index, int n) {
        int size_val = size();

        if (index < 0 || index > size_val) {
            cerr << "Invalid index! Must be between 0 and " << size_val << ".\n";
            return;
        }

        // Case 1: Insert at the beginning
        if (index == 0) {
            push_front(n);
            return;
        }

        // Case 2: Insert at the end
        if (index == size_val) {
            push_end(n);
            return;
        }

        // Case 3: Insert in the middle
        DNode* ptr = list_head;
        for (int i = 0; i < index - 1; ++i) {
            ptr = ptr->next();
        }
        // ptr now points to the node before insertion position
        DNode* new_node = new DNode(n, ptr->next(), ptr);
        ptr->next()->set_prev(new_node);  // Link backward
        ptr->set_next(new_node);          // Link forward
    }

    /* ------------------------------------------------------------
        FUNCTION: int pop_front()
        ------------------------------------------------------------
        Removes the first node from the list and returns its value.
    -------------------------------------------------------------*/
    int pop_front() {
        if (empty()) {
            cerr << "List is empty! Cannot pop front.\n";
            return -1;
        }

        int value = list_head->retrieve();
        DNode* temp = list_head;

        if (list_head == list_tail) {
            // Case 1: Only one node
            list_head = list_tail = nullptr;
        } else {
            // Case 2: More than one node
            list_head = list_head->next();
            list_head->set_prev(nullptr);
        }

        delete temp;
        return value;
    }

    /* ------------------------------------------------------------
        FUNCTION: int pop_end()
        ------------------------------------------------------------
        Removes the last node from the list and returns its value.
    -------------------------------------------------------------*/
    int pop_end() {
        if (empty()) {
            cerr << "List is empty! Cannot pop end.\n";
            return -1;
        }

        int value = list_tail->retrieve();
        DNode* temp = list_tail;

        if (list_head == list_tail) {
            // Case 1: Only one node
            list_head = list_tail = nullptr;
        } else {
            // Case 2: More than one node
            list_tail = list_tail->prev();
            list_tail->set_next(nullptr);
        }

        delete temp;
        return value;
    }

    /* ------------------------------------------------------------
        FUNCTION: int erase(int n)
        ------------------------------------------------------------
        Removes ALL nodes containing the value 'n' from the list.
        Returns the number of nodes removed.
    -------------------------------------------------------------*/
    int erase(int n) {
        int count_removed = 0;
        DNode* ptr = list_head;

        while (ptr != nullptr) {
            DNode* next_node = ptr->next(); // Store next node

            if (ptr->retrieve() == n) {
                if (ptr == list_head) {
                    pop_front(); // Handles head/tail update
                }
                else if (ptr == list_tail) {
                    pop_end(); // Handles head/tail update
                }
                else {
                    // Node is in the middle
                    ptr->prev()->set_next(ptr->next());
                    ptr->next()->set_prev(ptr->prev());
                    delete ptr;
                }
                ++count_removed;
            }
            ptr = next_node; // Move to the *original* next node
        }
        return count_removed;
    }

    /* ------------------------------------------------------------
        FUNCTION: void display() const
        ------------------------------------------------------------
        Prints all elements from head to tail.
    -------------------------------------------------------------*/
    void display() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        cout << "nullptr <- ";
        for (DNode* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout << ptr->retrieve();
            if (ptr->next() != nullptr)
                cout << " <-> ";
        }
        cout << " -> nullptr\n";
    }

    /* ------------------------------------------------------------
        FUNCTION: void display_reverse() const
        ------------------------------------------------------------
        Prints all elements from tail to head.
    -------------------------------------------------------------*/
    void display_reverse() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        cout << "nullptr <- ";
        for (DNode* ptr = list_tail; ptr != nullptr; ptr = ptr->prev()) {
            cout << ptr->retrieve();
            if (ptr->prev() != nullptr)
                cout << " <-> ";
        }
        cout << " -> nullptr\n";
    }
};

/* ===============================================================
    MAIN FUNCTION
    ----------------------------------------------------------------
    Demonstrates the DList functions.
==================================================================*/
int main() {
    DList lst; // create a new empty list

    cout << "Pushing front 10, 20, 30:\n";
    lst.push_front(10);
    lst.push_front(20);
    lst.push_front(30);
    lst.display(); // Expected: 30 <-> 20 <-> 10

    cout << "\nPushing end 40, 50:\n";
    lst.push_end(40);
    lst.push_end(50);
    lst.display(); // Expected: 30 <-> 20 <-> 10 <-> 40 <-> 50

    cout << "\nDisplay in reverse:\n";
    lst.display_reverse(); // Expected: 50 <-> 40 <-> 10 <-> 20 <-> 30

    cout << "\nFront element: " << lst.front() << endl;
    cout << "End element: " << lst.end() << endl;
    cout << "Size of list: " << lst.size() << endl;

    cout << "\nCounting how many times 20 appears: " << lst.count(20) << endl;

    cout << "\nErasing all nodes with value 20:\n";
    lst.erase(20);
    lst.display(); // Expected: 30 <-> 10 <-> 40 <-> 50

    cout << "\nPopping front: " << lst.pop_front() << endl;
    lst.display(); // Expected: 10 <-> 40 <-> 50

    cout << "\nPopping end: " << lst.pop_end() << endl;
    lst.display(); // Expected: 10 <-> 40

    cout << "\nErasing 10 and 40...\n";
    lst.erase(10);
    lst.erase(40);
    lst.display(); // Expected: List is empty.

    cout << "\nAttempting to pop from empty list:\n";
    lst.pop_front();

    cout << "\nProgram finished successfully.\n";

    return 0;
}