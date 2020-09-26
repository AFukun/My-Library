#pragma once
#include <initializer_list>

template<typename T>
class DoublyLinkedList {
public:
    struct Node {
        T value;
        Node *previous;
        Node *next;
        static const T null;
        Node();
        Node(T value, Node *previous, Node *next);
    };
    typedef unsigned size_t;
    const size_t npos = size_t(-1);
    // Constructors & Destructor
    DoublyLinkedList();
    DoublyLinkedList(std::initializer_list<T> init_list);
    ~DoublyLinkedList();
    // Methods

private:
    Node *head;
};