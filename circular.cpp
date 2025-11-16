#include <iostream>
using namespace std;

/* ===============================================================
    CLASS: Node
    ----------------------------------------------------------------
    This is the *exact same* Node class from your first
    singly linked list example. It has a value and one 'next'
    pointer. We can re-use it perfectly.
==================================================================*/
class Node {
private:
    int value;
    Node* next_node;

public:
    Node(int val = 0, Node* next = nullptr)
        : value(val), next_node(next) {}

    int retrieve() const { return value; }
    Node* next() const { return next_node; }
    void set_next(Node* next) { next_node = next; }

    friend class CList;
};

/* ===============================================================
    CLASS: CList
    ----------------------------------------------------------------
    The CList class represents a Circular Singly Linked List.
    It manages a circular chain of Nodes using only a single
    pointer: 'list_tail'.
     - If the list is empty, list_tail is nullptr.
     - If the list is not empty, list_tail points to the "last"
       node, and list_tail->next() points to the "first" node.
==================================================================*/
class CList {
private:
    Node* list_tail; // Points to the "last" node in the circle

public:
    /* ------------------------------------------------------------
        CONSTRUCTOR: CList()
        ------------------------------------------------------------
        Initializes the list to an empty state.
    -------------------------------------------------------------*/
    CList() : list_tail(nullptr) {}

    /* ------------------------------------------------------------
        DESTRUCTOR: ~CList()
        ------------------------------------------------------------
        Ensures all dynamically allocated memory is freed.
        This is more complex as it must break the cycle.
    -------------------------------------------------------------*/
    ~CList() {
        while (!empty())
            pop_front();
    }

    /* ------------------------------------------------------------
        FUNCTION: bool empty() const
        ------------------------------------------------------------
        Checks if the list has any nodes.
    -------------------------------------------------------------*/
    bool empty() const {
        return (list_tail == nullptr);
    }

    /* ------------------------------------------------------------
        FUNCTION: Node* head() const
        ------------------------------------------------------------
        Returns a pointer to the "first" node (the one after tail).
    -------------------------------------------------------------*/
    Node* head() const {
        if (empty()) return nullptr;
        return list_tail->next();
    }

    /* ------------------------------------------------------------
        FUNCTION: Node* tail() const
        ------------------------------------------------------------
        Returns a pointer to the "last" node.
    -------------------------------------------------------------*/
    Node* tail() const {
        return list_tail;
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
        return head()->retrieve(); // Get value from head
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
        return tail()->retrieve(); // Get value from tail
    }

    /* ------------------------------------------------------------
        FUNCTION: void push_front(int n)
        ------------------------------------------------------------
        Inserts a new node 'n' at the beginning of the list.
        (This is the same as adding *after* the tail).
    -------------------------------------------------------------*/
    void push_front(int n) {
        if (empty()) {
            // Case 1: List is empty
            Node* new_node = new Node(n);
            new_node->set_next(new_node); // Point to itself
            list_tail = new_node;
        } else {
            // Case 2: List is not empty
            Node* old_head = list_tail->next();
            Node* new_node = new Node(n, old_head);
            list_tail->set_next(new_node);
        }
    }

    /* ------------------------------------------------------------
        FUNCTION: void push_end(int n)
        ------------------------------------------------------------
        Adds a new node 'n' to the end of the list.
        (This means it becomes the new tail).
    -------------------------------------------------------------*/
    void push_end(int n) {
        if (empty()) {
            // Case 1: List is empty (same as push_front)
            push_front(n);
        } else {
            // Case 2: List is not empty
            Node* old_head = list_tail->next();
            Node* new_node = new Node(n, old_head);
            list_tail->set_next(new_node);
            list_tail = new_node; // The only difference
        }
    }

    /* ------------------------------------------------------------
        FUNCTION: void push_between(int index, int n)
        ------------------------------------------------------------
        Inserts a new node with value 'n' at the specified index
        in the circular list. Index 0 inserts at the beginning (after tail).
        For a circular list of size N, valid indices are 0 to N-1.
    -------------------------------------------------------------*/
    void push_between(int index, int n) {
        if (empty()) {
            cerr << "Cannot insert in empty list! Use push_front first.\n";
            return;
        }

        int size_val = size();
        if (index < 0 || index >= size_val) {
            cerr << "Invalid index! Must be between 0 and " << (size_val - 1) << ".\n";
            return;
        }

        // Case 1: Insert at the beginning (index 0)
        if (index == 0) {
            push_front(n);
            return;
        }

        // Case 2: Insert in the middle or at the position before tail
        Node* ptr = head();
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
    -------------------------------------------------------------*/
    int pop_front() {
        if (empty()) {
            cerr << "List is empty! Cannot pop front.\n";
            return -1;
        }

        Node* old_head = list_tail->next();
        int value = old_head->retrieve();

        if (old_head == list_tail) {
            // Case 1: Only one node
            delete old_head;
            list_tail = nullptr;
        } else {
            // Case 2: More than one node
            list_tail->set_next(old_head->next());
            delete old_head;
        }
        return value;
    }

    /* ------------------------------------------------------------
        FUNCTION: int pop_end()
        ------------------------------------------------------------
        Removes the last node from the list and returns its value.
        This is slow (O(N)) as we must find the *new* last node.
    -------------------------------------------------------------*/
    int pop_end() {
        if (empty()) {
            cerr << "List is empty! Cannot pop end.\n";
            return -1;
        }

        Node* old_tail = list_tail;
        int value = old_tail->retrieve();

        if (list_tail->next() == list_tail) {
            // Case 1: Only one node
            delete old_tail;
            list_tail = nullptr;
        } else {
            // Case 2: More than one node
            // Must traverse to find the node *before* the tail
            Node* ptr = list_tail->next();
            while (ptr->next() != list_tail) {
                ptr = ptr->next();
            }
            // ptr is now the new tail
            ptr->set_next(list_tail->next()); // Link new tail to head
            list_tail = ptr;                  // Update master pointer
            delete old_tail;
        }
        return value;
    }

    /* ------------------------------------------------------------
        FUNCTION: int erase(int index)
        ------------------------------------------------------------
        Removes the node at the given index (0-based) and returns
        its value. Returns -1 if the index is invalid or list empty.
    -------------------------------------------------------------*/
    int erase(int index) {
        if (empty()) {
            cerr << "List is empty! Cannot erase.\n";
            return -1;
        }

        int size_val = size();
        if (index < 0 || index >= size_val) {
            cerr << "Invalid index! Must be between 0 and " << (size_val - 1) << ".\n";
            return -1;
        }

        // Special case: Erase the first node (index 0)
        if (index == 0) {
            return pop_front();
        }

        // Special case: Erase the last node
        if (index == size_val - 1) {
            return pop_end();
        }

        // General case: Find the node before the one to erase
        Node* ptr = head();
        for (int i = 0; i < index - 1; ++i) {
            ptr = ptr->next();
        }

        // ptr now points to the node *before* the one we want to delete
        Node* to_delete = ptr->next();
        int value = to_delete->retrieve();

        // Link the previous node to the next node, skipping to_delete
        ptr->set_next(to_delete->next());
        delete to_delete;

        return value;
    }

    /* ------------------------------------------------------------
        FUNCTION: void display()
        ------------------------------------------------------------
        Prints all elements in the list, starting from the head.
    -------------------------------------------------------------*/
    void display() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        Node* ptr = head();
        cout << "Head -> ";
        do {
            cout << ptr->retrieve() << " -> ";
            ptr = ptr->next();
        } while (ptr != head()); // Loop until we're back to the head

        cout << "(Back to Head)\n";
        cout << "(Tail is: " << list_tail->retrieve() << ")\n";
    }

    /* ------------------------------------------------------------
        FUNCTION: int size() const
        ------------------------------------------------------------
        Traverses the list and counts the nodes.
    -------------------------------------------------------------*/
    int size() const {
        if (empty()) return 0;

        int count = 0;
        Node* ptr = head();
        do {
            ++count;
            ptr = ptr->next();
        } while (ptr != head());
        
        return count;
    }
};

/* ===============================================================
    MAIN FUNCTION
    ----------------------------------------------------------------
    Demonstrates the CList functions.
==================================================================*/
int main() {
    CList lst; // create a new empty list

    cout << "Pushing front 10, 20, 30:\n";
    lst.push_front(10);
    lst.push_front(20);
    lst.push_front(30);
    lst.display(); 
    // Expected: Head -> 30 -> 20 -> 10 -> (Back to Head)
    // (Tail is: 10)

    cout << "\nPushing end 40, 50:\n";
    lst.push_end(40);
    lst.push_end(50);
    lst.display(); 
    // Expected: Head -> 30 -> 20 -> 10 -> 40 -> 50 -> (Back to Head)
    // (Tail is: 50)

    cout << "\nFront element: " << lst.front() << endl; // 30
    cout << "End element: " << lst.end() << endl;     // 50
    cout << "Size: " << lst.size() << endl;           // 5

    cout << "\nPopping front: " << lst.pop_front() << endl; // 30
    lst.display();
    // Expected: Head -> 20 -> 10 -> 40 -> 50 -> (Back to Head)
    // (Tail is: 50)

    cout << "\nPopping end: " << lst.pop_end() << endl; // 50
    lst.display();
    // Expected: Head -> 20 -> 10 -> 40 -> (Back to Head)
    // (Tail is: 40)

    cout << "\nPopping end: " << lst.pop_end() << endl; // 40
    lst.display();
    // Expected: Head -> 20 -> 10 -> (Back to Head)
    // (Tail is: 10)

    cout << "\nPopping front: " << lst.pop_front() << endl; // 20
    lst.display();
    // Expected: Head -> 10 -> (Back to Head)
    // (Tail is: 10)

    cout << "\nPopping end: " << lst.pop_end() << endl; // 10
    lst.display();
    // Expected: List is empty.

    cout << "\nProgram finished successfully.\n";

    return 0;
}