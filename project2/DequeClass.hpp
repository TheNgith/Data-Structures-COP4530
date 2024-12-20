#ifndef DEQUECLASS_H
#define DEQUECLASS_H

#include <string>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class Deque {
private:
    Node<T>* front;
    Node<T>* back;
    size_t size;

public:
    Deque();
    
    ~Deque();
    
    void push_front(const T& value);
    
    void push_back(const T& value);
    
    void pop_front();
    
    void pop_back();
    
    T frontValue() const;
    
    T backValue() const;
    
    bool isEmpty() const;
    
    size_t getSize() const;
    
    void clear();
};

#endif /* DEQUECLASS_H */