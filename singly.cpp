#include <iostream>
using namespace std;

/* ===============================================================
   CLASS: Node
   ----------------------------------------------------------------
   Each Node object represents a single element (node) in the
   linked list. Every node contains two important pieces of data:
     1. An integer 'value' that stores the actual data of the node.
     2. A pointer 'next_node' which points to the next node in the
        linked list (or nullptr if it is the last node).
==================================================================*/
class Node {
private:
    int value;          // The data stored in the node
    Node* next_node;    // Pointer to the next node in the list

public:
    /* ------------------------------------------------------------
       CONSTRUCTOR: Node(int val = 0, Node* next = nullptr)
       ------------------------------------------------------------
       This constructor allows creating a node with a specified
       value and a pointer to the next node. Both parameters have
       default values, so calling "Node()" will create a node with
       value = 0 and next_node = nullptr.
    -------------------------------------------------------------*/
    Node(int val = 0, Node* next = nullptr)
        : value(val), next_node(next) {}

    /* ------------------------------------------------------------
       ACCESSOR: int retrieve() const
       ------------------------------------------------------------
       Returns the data value stored in the current node.
       Marked as 'const' since it doesn’t modify the node.
    -------------------------------------------------------------*/
    int retrieve() const { return value; }

    /* ------------------------------------------------------------
       ACCESSOR: Node* next() const
       ------------------------------------------------------------
       Returns the address of the next node (the next pointer).
       Also marked as 'const' since it does not modify the object.
    -------------------------------------------------------------*/
    Node* next() const { return next_node; }

    /* ------------------------------------------------------------
       MUTATOR: void set_next(Node* next)
       ------------------------------------------------------------
       This function changes the link of the current node by
       setting its 'next_node' pointer to another node address.
       This allows updating connections between nodes dynamically.
    -------------------------------------------------------------*/
    void set_next(Node* next) { next_node = next; }

    // Friend class declaration:
    // Gives the 'List' class permission to access Node’s private
    // data members (value and next_node) directly.
    friend class List;
};

/* ===============================================================
   CLASS: List
   ----------------------------------------------------------------
   The List class represents a singly linked list. It manages
   a collection of Node objects using a single pointer 'list_head'
   that always points to the first node (head) of the list.
==================================================================*/
class List {
private:
    Node* list_head;  // Points to the first node in the list (nullptr if empty)

public:
    /* ------------------------------------------------------------
       CONSTRUCTOR: List()
       ------------------------------------------------------------
       Initializes the linked list to an empty state.
       'list_head' is set to nullptr to indicate there are no nodes.
    -------------------------------------------------------------*/
    List() : list_head(nullptr) {}

    /* ------------------------------------------------------------
       DESTRUCTOR: ~List()
       ------------------------------------------------------------
       The destructor ensures that all dynamically allocated memory
       used by nodes is properly freed before the list object is
       destroyed. It repeatedly calls pop_front() until the list is
       empty, deleting all nodes one by one.
    -------------------------------------------------------------*/
    ~List() {
        while (!empty())
            pop_front();  // delete first node repeatedly
    }

    /* ------------------------------------------------------------
       FUNCTION: bool empty() const
       ------------------------------------------------------------
       Checks whether the linked list has any nodes.
       Returns true if list_head is nullptr (no nodes), otherwise false.
    -------------------------------------------------------------*/
    bool empty() const {
        return (list_head == nullptr);
    }

    /* ------------------------------------------------------------
       FUNCTION: int size() const
       ------------------------------------------------------------
       Traverses the entire linked list and counts how many nodes exist.
       Uses a loop starting from the head node and follows the chain
       of next pointers until reaching nullptr.
    -------------------------------------------------------------*/
    int size() const {
        int count = 0;
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            ++count;
        return count;
    }

    /* ------------------------------------------------------------
       FUNCTION: int front() const
       ------------------------------------------------------------
       Returns the data value of the first node (head) in the list.
       If the list is empty, prints an error message and returns -1.
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
       Returns the data value of the last node (tail) in the list.
       If empty, returns -1.
       This function iterates until it finds the node whose 'next'
       pointer is nullptr (the end of the list).
    -------------------------------------------------------------*/
    int end() const {
        if (empty()) {
            cerr << "List is empty! Cannot access end element.\n";
            return -1;
        }

        Node* ptr = list_head;
        while (ptr->next() != nullptr)
            ptr = ptr->next();
        return ptr->retrieve();
    }

    /* ------------------------------------------------------------
       FUNCTION: Node* head() const
       ------------------------------------------------------------
       Returns the head pointer (address of the first node).
       This can be useful when another function needs to iterate
       through the list.
    -------------------------------------------------------------*/
    Node* head() const {
        return list_head;
    }

    /* ------------------------------------------------------------
       FUNCTION: int count(int n) const
       ------------------------------------------------------------
       Counts how many nodes contain the specified integer value 'n'.
       The loop traverses each node and compares its stored value to 'n'.
    -------------------------------------------------------------*/
    int count(int n) const {
        int node_count = 0;
        for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            if (ptr->retrieve() == n)
                ++node_count;
        }
        return node_count;
    }

    /* ------------------------------------------------------------
       FUNCTION: void push_front(int n)
       ------------------------------------------------------------
       Inserts a new node containing 'n' at the beginning of the list.
       1. Create a new node whose next pointer points to the current head.
       2. Update 'list_head' to point to the new node.
    -------------------------------------------------------------*/
    void push_front(int n) {
        Node* new_node = new Node(n, list_head);
        list_head = new_node;
    }

    /* ------------------------------------------------------------
       FUNCTION: void push_end(int n)
       ------------------------------------------------------------
       Adds a new node with value 'n' to the end of the list.
       1. If the list is empty, simply set the head to the new node.
       2. Otherwise, traverse until reaching the last node and make
          its 'next' pointer refer to the new node.
    -------------------------------------------------------------*/
    void push_end(int n) {
        Node* new_node = new Node(n, nullptr);

        if (empty()) {
            list_head = new_node;
            return;
        }

        Node* ptr = list_head;
        while (ptr->next() != nullptr)
            ptr = ptr->next();
        ptr->set_next(new_node);
    }

    /* ------------------------------------------------------------
       FUNCTION: void push_between(int index, int n)
       ------------------------------------------------------------
       Inserts a new node with value 'n' at the specified index.
       Index 0 inserts before the first node (same as push_front).
       If index equals the list size, it appends (same as push_end).
       For indices in between, inserts the node after index-1 position.
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
        Node* ptr = list_head;
        for (int i = 0; i < index - 1; ++i) {
            ptr = ptr->next();
        }
        // ptr now points to the node before insertion position
        Node* new_node = new Node(n, ptr->next());
        ptr->set_next(new_node);
    }

    /* ------------------------------------------------------------
       FUNCTION: int pop_front()
       ------------------------------------------------------------
       Removes the first node from the list and returns its value.
       1. Check if the list is empty.
       2. Store the value of the first node.
       3. Move the head pointer to the second node.
       4. Delete the first node to free memory.
    -------------------------------------------------------------*/
    int pop_front() {
        if (empty()) {
            cerr << "List is empty! Cannot pop front.\n";
            return -1;
        }

        int value = list_head->retrieve();
        Node* temp = list_head;
        list_head = list_head->next();
        delete temp;
        return value;
    }

    /* ------------------------------------------------------------
       FUNCTION: int pop_end()
       ------------------------------------------------------------
       Removes the last node from the list and returns its value.
       1. If the list is empty, print an error.
       2. If there is only one node, delete it and reset head.
       3. Otherwise, iterate to the second-last node and remove the last one.
    -------------------------------------------------------------*/
    int pop_end() {
        if (empty()) {
            cerr << "List is empty! Cannot pop end.\n";
            return -1;
        }

        // Case 1: only one node
        if (list_head->next() == nullptr) {
            int value = list_head->retrieve();
            delete list_head;
            list_head = nullptr;
            return value;
        }

        // Case 2: more than one node
        Node* ptr = list_head;
        while (ptr->next()->next() != nullptr)
            ptr = ptr->next();

        int value = ptr->next()->retrieve();
        delete ptr->next();
        ptr->set_next(nullptr);
        return value;
    }

    /* ------------------------------------------------------------
       FUNCTION: int erase(int n)
       ------------------------------------------------------------
       Removes ALL nodes containing the value 'n' from the list.
       Returns the number of nodes removed.
       Steps:
         1. Handle the special case where one or more head nodes
            contain 'n' (since the head pointer must be updated).
         2. Traverse through the list while checking next nodes.
         3. If a node’s next node contains 'n', unlink and delete it.
    -------------------------------------------------------------*/
    int erase(int n) {
        int count_removed = 0;

        // Handle nodes at the beginning of the list
        while (list_head != nullptr && list_head->retrieve() == n) {
            Node* temp = list_head;
            list_head = list_head->next();
            delete temp;
            ++count_removed;
        }

        // Now handle remaining nodes
        Node* ptr = list_head;
        while (ptr != nullptr && ptr->next() != nullptr) {
            if (ptr->next()->retrieve() == n) {
                Node* temp = ptr->next();
                ptr->next_node = ptr->next()->next();  // bypass deleted node
                delete temp;
                ++count_removed;
            } else {
                ptr = ptr->next();  // move to next node
            }
        }

        return count_removed;
    }

    /* ------------------------------------------------------------
       FUNCTION: void display() const
       ------------------------------------------------------------
       Prints all elements of the linked list in sequence.
       Displays each node’s data followed by "->", ending with "nullptr".
    -------------------------------------------------------------*/
    void display() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            cout << ptr->retrieve() << " -> ";
        cout << "nullptr\n";
    }
};

/* ===============================================================
   MAIN FUNCTION
   ----------------------------------------------------------------
   Demonstrates how all the linked list functions work. It performs
   various operations such as insertion, deletion, traversal, and
   counting while printing intermediate results for clarity.
==================================================================*/
int main() {
    List lst;  // create a new empty linked list

    cout << "Pushing front 10, 20, 30 (30 will become the head):\n";
    lst.push_front(10);
    lst.push_front(20);
    lst.push_front(30);
    lst.display();  // Expected: 30 -> 20 -> 10 -> nullptr

    cout << "\nPushing end 40, 50 (these will be appended at tail):\n";
    lst.push_end(40);
    lst.push_end(50);
    lst.display();  // Expected: 30 -> 20 -> 10 -> 40 -> 50 -> nullptr

    cout << "\nFront element: " << lst.front() << endl;
    cout << "End element: " << lst.end() << endl;
    cout << "Size of list: " << lst.size() << endl;

    cout << "\nCounting how many times 20 appears: " << lst.count(20) << endl;

    cout << "\nErasing all nodes with value 20:\n";
    lst.erase(20);
    lst.display();

    cout << "\nPopping front (removes head node): " << lst.pop_front() << endl;
    lst.display();

    cout << "\nPopping end (removes last node): " << lst.pop_end() << endl;
    lst.display();

    cout << "\nIs list empty? " << (lst.empty() ? "Yes" : "No") << endl;
    cout << "Final size of list: " << lst.size() << endl;

    cout << "\nProgram finished successfully.\n";

    return 0;
}
