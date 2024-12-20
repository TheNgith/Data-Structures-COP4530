/*
Tam Nguyen - U99681342
Thinh Nguyen - U38848480
COP4530 - Project 2

This file contains the implementation of the Deque class
This Deque class uses a doubly linked list to replicate the functionality of a deque
*/

#include "DequeClass.hpp"
#include <stdexcept>

template <typename T>
Deque<T>::Deque() : front(nullptr), back(nullptr), size(0) {}

template <typename T>
Deque<T>::~Deque() {
    clear();
}

template <typename T>
void Deque<T>::push_front(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        front = back = newNode;
    } else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }
    size++;
}

template <typename T>
void Deque<T>::push_back(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        front = back = newNode;
    } else {
        newNode->prev = back;
        back->next = newNode;
        back = newNode;
    }
    size++;
}

template <typename T>
void Deque<T>::pop_front() {
    if (!isEmpty()) {
        Node<T>* temp = front;
        front = front->next;
        if (front) {
            front->prev = nullptr;
        } else {
            back = nullptr;
        }
        delete temp;
        size--;
    }
}

template <typename T>
void Deque<T>::pop_back() {
    if (!isEmpty()) {
        Node<T>* temp = back;
        back = back->prev;
        if (back) {
            back->next = nullptr;
        } else {
            front = nullptr;
        }
        delete temp;
        size--;
    }
}

template <typename T>
T Deque<T>::frontValue() const {
    if (!isEmpty()) {
        return front->data;
    }
    throw std::out_of_range("Deque is empty");
}

template <typename T>
T Deque<T>::backValue() const {
    if (!isEmpty()) {
        return back->data;
    }
    throw std::out_of_range("Deque is empty");
}

template <typename T>
bool Deque<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
size_t Deque<T>::getSize() const {
    return size;
}

template <typename T>
void Deque<T>::clear() {
    while (!isEmpty()) {
        pop_front();
    }
}