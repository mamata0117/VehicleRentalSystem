#ifndef STACK_H
#define STACK_H

#include <string>

using namespace std;

template <typename T>
struct StackNode {
    T data;
    StackNode* next;
};

template <typename T>
class Stack {
private:
    StackNode<T>* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T value) {
        StackNode<T>* newNode = new StackNode<T>();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!isEmpty()) {
            StackNode<T>* temp = top;
            top = top->next;
            delete temp;
        }
    }

    T peek() {
        if (!isEmpty()) {
            return top->data;
        }
        return T();
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

#endif
