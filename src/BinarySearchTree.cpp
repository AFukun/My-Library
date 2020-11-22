#include "BinarySearchTree.hpp"
#include <algorithm>
#include <iostream>

template<typename ValueType, typename Compare>
BinarySearchTree<ValueType, Compare>::BinarySearchTree() :root(nullptr) {}

template<typename ValueType, typename Compare>
BinarySearchTree<ValueType, Compare>::BinarySearchTree(std::initializer_list<ValueType> ini_list) : root(nullptr) {
	std::vector<ValueType> inorderSequence(ini_list);
	sort(inorderSequence.begin(), inorderSequence.begin(), Compare());
	buildFromInorderSequence(inorderSequence, 0, inorderSequence.size());
}

// template<typename ValueType, typename Compare>
// BinarySearchTree<ValueType, Compare>::BinarySearchTree(BinarySearchTree &other) {

// }

template<typename ValueType, typename Compare>
BinarySearchTree<ValueType, Compare>::~BinarySearchTree() {
	clear();
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::insert(ValueType value) {
	insertAt(root, value);
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::remove(ValueType value) {
	removeValueFrom(root, value);
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::clear() {
	deleteNode(root);
}

template<typename ValueType, typename Compare>
std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getInorderSequence() {
	std::vector<ValueType> result;
	travelInorder(result, root);
	return result;
}

template<typename ValueType, typename Compare>
std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getPreorderSequence() {
	std::vector<ValueType> result;
	travelPreorder(result, root);
	return result;
}

template<typename ValueType, typename Compare>
std::vector<ValueType> BinarySearchTree<ValueType, Compare>::getPostorderSequence() {
	std::vector<ValueType> result;
	travelPostorder(result, root);
	return result;
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::buildFromInorderSequence(std::vector<ValueType> &seq, size_t begin, size_t end) {
	if (begin >= end) { return; }
	size_t mid = begin + ( end - begin ) / 2;
	insert(seq[mid]);
	buildFromInorderSequence(seq, begin, mid);
	buildFromInorderSequence(seq, mid + 1, end);
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::insertAt(Node *&node, ValueType value) {
	if (node == nullptr)  node = new Node(value);
	if (Compare()( value, node->value )) { insertAt(node->left, value); }
	if (Compare()( node->value, value )) { insertAt(node->right, value); }
	if (value == node->value && node->deleted) { node->deleted = false; }
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::travelInorder(std::vector<ValueType> &output, Node *node) {
	if (node == nullptr) { return; }
	travelInorder(output, node->left);
	if (!node->deleted) { output.push_back(node->value); }
	travelInorder(output, node->right);
}


template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::travelPreorder(std::vector<ValueType> &output, Node *node) {
	if (node == nullptr) { return; }
	if (!node->deleted) { output.push_back(node->value); }
	travelPreorder(output, node->left);
	travelPreorder(output, node->right);
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::travelPostorder(std::vector<ValueType> &output, Node *node) {
	if (node == nullptr) { return; }
	travelPostorder(output, node->left);
	travelPostorder(output, node->right);
	if (!node->deleted) { output.push_back(node->value); }
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::deleteNode(Node *node) {
	if (node->left != nullptr) { deleteNode(node->left); }
	if (node->right != nullptr) { deleteNode(node->right); }
	delete node;
}

template<typename ValueType, typename Compare>
void BinarySearchTree<ValueType, Compare>::removeValueFrom(Node *node, ValueType value) {
	if (node == nullptr) { return; }
	if (node->value == value) { node->deleted = true; }
	if (Compare()( value, node->value )) { removeValueFrom(node->left, value); }
	if (Compare()( node->value, value )) { removeValueFrom(node->right, value); }
}

template class BinarySearchTree<int>;
template class BinarySearchTree<float>;
template class BinarySearchTree<double>;



