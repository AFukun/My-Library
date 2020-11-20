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

// template<typename ValueType, typename Compare>
// bool BinarySearchTree<ValueType, Compare>::insert(ValueType value) {

// }

// template<typename ValueType, typename Compare>
// bool BinarySearchTree<ValueType, Compare>::remove(ValueType value) {

// }

template<typename ValueType, typename Compare>
std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getInorderSequence() {

}

template<typename ValueType, typename Compare>
std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getPreorderSequence() {

}

template<typename ValueType, typename Compare>
std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getPostorderSequence() {

}

template class BinarySearchTree<int>;
