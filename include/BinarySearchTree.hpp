#pragma once
#include <vector>
#include <initializer_list>
#include <functional>

template<typename ValueType, typename Compare = std::less<ValueType> >
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(std::initializer_list<ValueType> initialList);
    // BinarySearchTree(std::vector<ValueType> &inorderSequence, std::vector<ValueType> &preorderSequence);
    BinarySearchTree(BinarySearchTree &other);
    ~BinarySearchTree();
    void insert(ValueType value);
    void remove(ValueType value);
    void clear();
    std::vector<ValueType> getInorderSequence();
    std::vector<ValueType> getPreorderSequence();
    std::vector<ValueType> getPostorderSequence();

private:
    struct Node {
        ValueType value;
        Node *left;
        Node *right;
        bool deleted;
        Node(ValueType value) :value(value), left(nullptr), right(nullptr), deleted(false) {}
    };
    Node *root;

    void insertAt(Node *&node, ValueType value);
    void buildFromInorderSequence(std::vector<ValueType> &inputSequence, size_t begin, size_t end);
    void travelInorder(std::vector<ValueType> &outputSequence, Node *node);
    void travelPreorder(std::vector<ValueType> &outputSequence, Node *node);
    void travelPostorder(std::vector<ValueType> &outputSequence, Node *node);
    void deleteNode(Node *node);
    void removeValueFrom(Node *node, ValueType value);
};