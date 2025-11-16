#include <iostream>
using namespace std;

// --- Node Class (Same as singly.cpp) ---
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

    friend class Stack; // Stack class needs access to Node's private members
};

/* ===============================================================
    CLASS: Stack
    ----------------------------------------------------------------
    Implements a Stack (LIFO - Last In, First Out) using a
    Singly Linked List, where the list_head acts as the 'top'
    of the stack.
==================================================================*/
class Stack {
private:
    Node* list_head; // Points to the top of the stack (first node)
    int stack_size;  // Tracks the number of elements

public:
    /* ------------------------------------------------------------
        CONSTRUCTOR: Stack()
        ------------------------------------------------------------
        Initializes the stack to an empty state.
    -------------------------------------------------------------*/
    Stack() : list_head(nullptr), stack_size(0) {}

    /* ------------------------------------------------------------
        DESTRUCTOR: ~Stack()
        ------------------------------------------------------------
        Frees all dynamically allocated memory by repeatedly
        calling pop() until the stack is empty.
    -------------------------------------------------------------*/
    ~Stack() {
        while (!empty())
            pop();
    }

    /* ------------------------------------------------------------
        FUNCTION: bool empty() const
        ------------------------------------------------------------
        Checks if the stack has any elements. (O(1))
    -------------------------------------------------------------*/
    bool empty() const {
        return (list_head == nullptr);
    }

    /* ------------------------------------------------------------
        FUNCTION: int size() const
        ------------------------------------------------------------
        Returns the number of elements in the stack. (O(1))
    -------------------------------------------------------------*/
    int size() const {
        return stack_size;
    }

    /* ------------------------------------------------------------
        FUNCTION: void push(int n)
        ------------------------------------------------------------
        Adds a new element 'n' to the top of the stack.
        This is equivalent to 'push_front' in a linked list. (O(1))
    -------------------------------------------------------------*/
    void push(int n) {
        Node* new_node = new Node(n, list_head);
        list_head = new_node;
        stack_size++;
    }

    /* ------------------------------------------------------------
        FUNCTION: int pop()
        ------------------------------------------------------------
        Removes and returns the element at the top of the stack.
        This is equivalent to 'pop_front' in a linked list. (O(1))
    -------------------------------------------------------------*/
    int pop() {
        if (empty()) {
            cerr << "Stack is empty! Cannot pop.\n";
            return -1;
        }

        int value = list_head->retrieve();
        Node* temp = list_head;
        list_head = list_head->next();
        delete temp;
        stack_size--;
        return value;
    }

    /* ------------------------------------------------------------
        FUNCTION: int top() const
        ------------------------------------------------------------
        Returns the element at the top of the stack without removing it.
        This is equivalent to 'front' in a linked list. (O(1))
    -------------------------------------------------------------*/
    int top() const {
        if (empty()) {
            cerr << "Stack is empty! Cannot access top element.\n";
            return -1;
        }
        return list_head->retrieve();
    }

    /* ------------------------------------------------------------
        FUNCTION: void display() const
        ------------------------------------------------------------
        Prints all elements from top to bottom.
    -------------------------------------------------------------*/
    void display() const {
        if (empty()) {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "TOP -> ";
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout << ptr->retrieve();
            if (ptr->next() != nullptr)
                cout << " -> ";
        }
        cout << " -> BOTTOM\n";
    }
};

/* ===============================================================
    MAIN FUNCTION
    ----------------------------------------------------------------
    Demonstrates the Stack functions.
==================================================================*/
int main() {
    Stack s; // create a new empty stack

    cout << "Pushing 10, 20, 30 onto the stack:\n";
    s.push(10);
    s.push(20);
    s.push(30);
    s.display(); // Expected: TOP -> 30 -> 20 -> 10 -> BOTTOM

    cout << "\nTop element: " << s.top() << endl; // 30
    cout << "Size of stack: " << s.size() << endl; // 3

    cout << "\nPopping: " << s.pop() << endl; // 30
    s.display(); // Expected: TOP -> 20 -> 10 -> BOTTOM

    cout << "\nPushing 40:\n";
    s.push(40);
    s.display(); // Expected: TOP -> 40 -> 20 -> 10 -> BOTTOM

    cout << "\nPopping: " << s.pop() << endl; // 40
    cout << "Popping: " << s.pop() << endl; // 20
    cout << "Popping: " << s.pop() << endl; // 10
    s.display(); // Expected: Stack is empty.

    cout << "\nIs stack empty? " << (s.empty() ? "Yes" : "No") << endl;

    cout << "\nProgram finished successfully.\n";

    return 0;
}