#pragma once
#include <initializer_list>
#include <iostream>

// For userdefined type: "<" & nullValue defination are required
// To install nullValue:
// template <>
// const UserDefinedType Node<UserDefinedType>::null = userDefinedNullValue;


template <typename T>
class LinkedList {
public:
    // Types & Consts Defination
    struct Node {
        T value;
        Node *next;

        static const T null;
        Node() : value(null), next(nullptr) {};
        Node(T value) : value(value), next(nullptr) {};
    };
    typedef unsigned int size_t;
    const size_t npos = size_t(-1);
    // Constructors & Destructor
    LinkedList();
    LinkedList(LinkedList<T> &other);
    LinkedList(std::initializer_list<T> init_list);
    ~LinkedList();
    // Methods
    size_t size() const;
    void push_front(const T &value);
    void push_back(const T &value);
    T &operator[](size_t index);
    size_t searchByValue(T value) const;
    bool deleteByIndex(size_t index);
    bool deleteByValue(const T &value);
    LinkedList<T> &sort();
    LinkedList<T> &merge(LinkedList<T> &other);
    void reverse();
    void print() const;
    // Friends
    template <typename U>
    friend std::ostream &operator<<(std::ostream &cout, LinkedList<U> &list) {
        list.print();
        return cout;
    }

private:
    Node *head;
    Node *tail;
    size_t _size;
};

