#pragma once
#include <vector>
#include <initializer_list>
#include <functional>
#include <iterator>

template<typename ValueType, typename Compare = std::less<ValueType>>
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(std::initializer_list<ValueType> ini_list);
    BinarySearchTree(std::vector<ValueType> &inorder_seq, std::vector<ValueType> &preorder_seq);
    BinarySearchTree(BinarySearchTree &other);
    ~BinarySearchTree();
    bool insert(ValueType value);
    bool remove(ValueType value);
    std::vector<ValueType> getInorderSequence();
    std::vector<ValueType> getPreorderSequence();
    std::vector<ValueType> getPostorderSequence();
    void clear();

private:
    struct Node {
        ValueType value;
        Node *left;
        Node *right;
        Node(ValueType value) :value(value), left(nullptr), right(nullptr) {}
    };

    Node *root;

    bool (*compare)(ValueType &lhs, ValueType &rhs);

    void getBinaryDividedSequence(std::vector<ValueType> dstSeq, std::iterator<std::random_access_iterator_tag, ValueType> begin, std::iterator<std::random_access_iterator_tag, ValueType> end);
};