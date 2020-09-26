#include "DoublyLinkedList.hpp"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

template<typename T>
const T DoublyLinkedList<T>::Node::null = T(0);

template<>
const std::string DoublyLinkedList<string>::Node::null = "";

template<typename T>
DoublyLinkedList<T>::Node::Node() :value(null), previous(nullptr), next(nullptr) {}
template<typename T>
DoublyLinkedList<T>::Node::Node(T value, DoublyLinkedList<T>::Node *previous, DoublyLinkedList<T>::Node *next)
	: value(value), previous(previous), next(next) {};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	head = new Node();
	head->next = head;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node *toDelete;
	while (head != nullptr) {
		toDelete = head;
		head = head->next;
		delete toDelete;
	}
}


