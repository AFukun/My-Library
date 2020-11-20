#include <string>
#include "LinkedList.hpp"

using std::cout;
using std::endl;
using std::string;

//Node Member
template <typename T>
const T LinkedList<T>::Node::null = T(0);
template <>
const std::string LinkedList<string>::Node::null = "null";

// Constructors & Destructor
template <typename T>
LinkedList<T>::LinkedList() {
    _size = 0;
    tail = head = new Node();
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &other) {
    Node *read = other.head;
    tail = head = new Node();
    _size = 0;
    while (read->next != nullptr) {
        read = read->next;
        push_back(read->value);
    }
}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> init_list) {
    tail = head = new Node();
    _size = 0;
    for (auto i = init_list.begin(); i != init_list.end(); i++) {
        push_back(*i);
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node *toDelete;

    while (head != nullptr) {
        toDelete = head;
        head = head->next;
        delete toDelete;
    }
    head = tail = nullptr;
}

// Methods
template <typename T>
typename LinkedList<T>::size_t LinkedList<T>::size() const {
    return _size;
}

template <typename T>
T &LinkedList<T>::operator[](size_t index) {
    try {
        if (_size == 0)
            throw "Empty list";
        if (index >= _size)
            throw "Index out of bounds. Return value in header.";
    } catch (char const *s) {
        cout << s << endl;
        return head->value;
    }

    Node *read = head;
    for (size_t i = 0; i <= index; i++)
        read = read->next;
    return read->value;
}

template <typename T>
typename LinkedList<T>::size_t LinkedList<T>::searchByValue(T value) const {
    Node *read = head->next;
    size_t index = 0;
    while (read != nullptr) {

        if (read->value == value) {
            return index;
        }
        read = read->next;
        index++;
    }
    return npos;
}

template <typename T>
bool LinkedList<T>::deleteByIndex(LinkedList<T>::size_t index) {
    if (index >= _size)
        return false;
    Node *read = head;

    for (size_t i = 0; i <= index; i++) {
        read = read->next;
    }
    return true;
}

template <typename T>
bool LinkedList<T>::deleteByValue(const T &value) {
    Node *read = head;
    while (read->next != nullptr) {
        if (read->next->value == value) {
            Node *toDelete = read->next;
            read->next = read->next->next;
            delete toDelete;
            return true;
        }
        read = read->next;
    }
    return false;
}

template <typename T>
LinkedList<T> &LinkedList<T>::sort() {
    Node *i = head->next, *j;
    while (i->next != nullptr) {
        j = i->next;
        while (j != nullptr) {
            if (i->value > j->value) {
                T temp = j->value;
                j->value = i->value;
                i->value = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
    return *this;
}

template<typename T>
void LinkedList<T>::push_front(const T &value) {
    Node *temp = new Node(value);
    temp->next = head->next;
    head->next = temp;
}

template <typename T>
void LinkedList<T>::push_back(const T &value) {
    tail->next = new Node(value);
    tail = tail->next;
    _size++;
}

template <typename T>
LinkedList<T> &LinkedList<T>::merge(LinkedList<T> &other) {
    Node *i = head->next, *j = other.head->next;
    LinkedList<T> *result = new LinkedList<T>;

    while (i != nullptr && j != nullptr) {
        if (i->value > j->value) {
            result->push_back(j->value);
            j = j->next;
        } else {
            result->push_back(i->value);
            i = i->next;
        }
    }
    while (i != nullptr) {
        result->push_back(i->value);
        i = i->next;
    }
    while (j != nullptr) {
        result->push_back(j->value);
        j = j->next;
    }
    return *result;
}




template <typename T>
void LinkedList<T>::print() const {
    Node *r = head->next;
    if (r == nullptr) {
        cout << "Empty List";
    }
    while (r != nullptr) {
        cout << r->value << ' ';
        r = r->next;
    }
}

template<typename T>
void LinkedList<T>::reverse() {
    Node *p = head->next, *q = nullptr, *r;
    while (p != nullptr) {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    head->next = q;
}

// template class LinkedList<char>;
// template class LinkedList<int>;
// template class LinkedList<double>;
// template class LinkedList<string>;
// To install UserDefinedType to LinkedList:
//   template class LinkedList<UserDefinedType>