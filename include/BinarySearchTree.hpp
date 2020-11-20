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
    void insert(ValueType value);
    void remove(ValueType value);
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
    void insertAt(Node *&node, ValueType value);
    void buildByInorderSequence(std::vector<ValueType> &seq, size_t begin, size_t end);
};