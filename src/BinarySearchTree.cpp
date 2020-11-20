#include "BinarySearchTree.hpp"
#include <algorithm>
#include <iostream>

template<typename ValueType, typename Compare>
BinarySearchTree<ValueType, Compare>::BinarySearchTree() :root(nullptr) {}

template<typename ValueType, typename Compare>
BinarySearchTree<ValueType, Compare>::BinarySearchTree(std::initializer_list<ValueType> ini_list) {
	std::vector<ValueType> inorderSequence(ini_list);
	sort(inorderSequence.begin(), inorderSequence.begin(), Compare());
}

// template<typename ValueType, typename Compare>
// BinarySearchTree<ValueType, Compare>::BinarySearchTree(std::vector<ValueType> &inorder_seq, std::vector<ValueType> &preorder_seq) {

// }


// template<typename ValueType, typename Compare>
// BinarySearchTree<ValueType, Compare>::BinarySearchTree(BinarySearchTree &other) {

// }

template<typename ValueType, typename Compare>
BinarySearchTree<ValueType, Compare>::~BinarySearchTree() {

}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::insert(ValueType value) {
	ValueType temp = value;
	return;
}

// template<typename ValueType, typename Compare>
// bool BinarySearchTree<ValueType, Compare>::remove(ValueType value) {

// }

// template<typename ValueType, typename Compare>
// std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getInorderSequence() {

// }

// template<typename ValueType, typename Compare>
// std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getPreorderSequence() {

// }

// template<typename ValueType, typename Compare>
// std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getPostorderSequence() {

// }

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::buildByInorderSequence(std::vector<ValueType> &seq, size_t begin, size_t end) {
	if (begin >= end) return;
	size_t mid = begin + (end - begin) / 2;
	insert(seq[mid]);
	buildByInorderSequence(seq, begin, mid);
	buildByInorderSequence(seq, mid + 1, end);
}

template class BinarySearchTree<int>;


template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::insertAt(Node *&node, ValueType value) {
	{
		if (node == nullptr)  node = new Node(value);
	}
}
