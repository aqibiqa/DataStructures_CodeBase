#include <iostream>
#include <stdexcept>
using namespace std;

// Define the maximum capacity
const int MAX_SIZE = 100;

class StaticStack {
private:
    int data[MAX_SIZE];
    int top_index; // Index of the top element

public:
    StaticStack() : top_index(-1) {}

    bool empty() const { return top_index == -1; }
    bool full() const { return top_index == MAX_SIZE - 1; }
    int size() const { return top_index + 1; }

    void push(int n) {
        if (full()) {
            throw overflow_error("Stack overflow: Cannot push, stack is full.");
        }
        data[++top_index] = n; // O(1)
    }

    int pop() {
        if (empty()) {
            throw out_of_range("Pop on empty stack");
        }
        return data[top_index--]; // O(1)
    }

    int top() const {
        if (empty()) {
            throw out_of_range("Top on empty stack");
        }
        return data[top_index]; // O(1)
    }

    void display() const {
        if (empty()) return;
        cout << "TOP -> ";
        for (int i = top_index; i >= 0; --i) {
            cout << data[i] << (i > 0 ? " -> " : "");
        }
        cout << " -> BOTTOM\n";
    }
};

int main() {
     StaticStack s;
     s.push(10);
     s.push(20);
     s.display(); // TOP -> 20 -> 10 -> BOTTOM
     cout << "Top: " << s.top() << endl; // 20
     cout << "Popped: " << s.pop() << endl; // 20
     s.display(); // TOP -> 10 -> BOTTOM
     return 0;
}