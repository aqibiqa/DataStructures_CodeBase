#include <iostream>
using namespace std;

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

    friend class Stack; 
};

class Stack {
private:
    Node* list_head;
    int stack_size; 

public:

    Stack() : list_head(nullptr), stack_size(0) {}

    
    ~Stack() {
        while (!empty())
            pop();
    }

    bool empty() const {
        return (list_head == nullptr);
    }

    int size() const {
        return stack_size;
    }
    void push(int n) {
        Node* new_node = new Node(n, list_head);
        list_head = new_node;
        stack_size++;
    }

 
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

    int top() const {
        if (empty()) {
            cerr << "Stack is empty! Cannot access top element.\n";
            return -1;
        }
        return list_head->retrieve();
    }

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
int main() {
    Stack s; 

    cout << "Pushing 10, 20, 30 onto the stack:\n";
    s.push(10);
    s.push(20);
    s.push(30);
    s.display(); 

    cout << "\nTop element: " << s.top() << endl; 
    cout << "Size of stack: " << s.size() << endl;

    cout << "\nPopping: " << s.pop() << endl;
    s.display();

    cout << "\nPushing 40:\n";
    s.push(40);
    s.display(); 

    cout << "\nPopping: " << s.pop() << endl; 
    cout << "Popping: " << s.pop() << endl; 
    cout << "Popping: " << s.pop() << endl; 
    s.display();

    cout << "\nIs stack empty? " << (s.empty() ? "Yes" : "No") << endl;

    cout << "\nProgram finished successfully.\n";

    return 0;
}
