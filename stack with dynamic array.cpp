#include <iostream>
#include <stdexcept>
using namespace std;

class DynamicStack {
private:
    int* data;
    int capacity;
    int top_index; 

    void resize() {
        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
        int* new_data = new int[new_capacity];

        for (int i = 0; i < capacity; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    DynamicStack() : data(nullptr), capacity(0), top_index(-1) {}
    ~DynamicStack() { delete[] data; }

    bool empty() const { return top_index == -1; }
    int size() const { return top_index + 1; }

    void push(int n) {
        if (size() == capacity) {
            resize(); 
        }
        data[++top_index] = n;
    }

    int pop() {
        if (empty()) {
            throw out_of_range("Pop on empty stack");
        }
        return data[top_index--]; 
    }

    int top() const {
        if (empty()) {
            throw out_of_range("Top on empty stack");
        }
        return data[top_index]; 
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
     DynamicStack s;
     s.push(1);
     s.push(2);
     s.push(3);
     s.display(); 
     cout << "Popped: " << s.pop() << endl; 
     s.display(); 
     return 0;
}
