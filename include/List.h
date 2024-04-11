#pragma once

#include <cstddef>
#include <stdexcept>

template<class T>
class List {
  public:
    List() = default;

  private:
    struct Node {
        Node *prev{};
        T key{};
        Node *next{};
    };
    Node *root{};
    Node *tail{};
    size_t size_{};
  public:
    size_t size() { return size_; };

    void insert_head(const T&);

    void insert_tail(const T&);

    void insert(const T&, Node * = nullptr);

    void erase(size_t);

    T& operator[](size_t);
};

template<class T>
void List<T>::insert_head(const T& x) {
    ++size_;
    if (root == nullptr) {
        root = tail = new Node;
        root->key = x;
        return;
    }
    Node *q = new Node;
    q->key = x;
    q->next = root;
    root->prev = q;
    root = q;
}

template<class T>
void List<T>::insert_tail(const T& x) {
    ++size_;
    if (tail == nullptr) {
        root = tail = new Node;
        tail->key = x;
        return;
    }
    Node *q = new Node;
    q->key = x;
    q->prev = tail;
    tail->next = q;
    tail = q;
}

template<class T>
void List<T>::insert(const T& x, List::Node *elem) {
    if (elem == nullptr) {
        insert_tail(x);
        return;
    }
    Node *q = new Node;
    q->next = elem->next;
    q->prev = elem;
    elem->next = q;
}

template<class T>
void List<T>::erase(size_t pos) {
    if (pos >= size_) throw std::out_of_range("Index is greater than List size");
    --size_;
    Node *q = root;
    while (pos--) {
        q = q->next;
    }
    if (q->prev != nullptr) {
        q->prev->next = q->next;
    } else {
        root = q->next;
    }
    if (q->next != nullptr) {
        q->next->prev = q->prev;
    }
    delete q;
}

template<class T>
T& List<T>::operator[](size_t pos) {
    if (pos >= size_) throw std::out_of_range("Index is greater than List size");
    Node *q = root;
    while (pos--) {
        q = q->next;
    }
    return q->key;
}
