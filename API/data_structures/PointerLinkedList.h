#pragma once

#include <iostream>

namespace engine {

    template <typename T>
    class PointerLinkedList;

    template <typename T>
    class PLLNode {
        friend class PointerLinkedList<T>;

    public:
        PLLNode(T* d) : next(nullptr), prev(nullptr), data(d) {}

        PLLNode(PLLNode<T>* p, T* d) : next(nullptr), prev(p), data(d) {}

        PLLNode(PLLNode<T>* n, PLLNode<T>* p, T* d) : next(n), prev(p), data(d) {}

        ~PLLNode() {}

        PLLNode<T>* getNext() const { return next; }
        PLLNode<T>* getPrev() const { return prev; }
        T* getData() const { return data; }

    private:
        PLLNode<T>* next;
        PLLNode<T>* prev;
        T* data;
    };

    template <typename T>
    class PointerLinkedList {
    public:
        PointerLinkedList() : head(nullptr), tail(nullptr), current_size(0) {}

        ~PointerLinkedList() { clear(); }

        PLLNode<T>* push_back(T* data) {
            if (head == nullptr) {
                head = new PLLNode<T>(data);
                tail = head;
                current_size = 1;
                return head;
            }

            PLLNode<T>* n = new PLLNode<T>(tail, data);
            tail->next = n;
            tail = n;
            current_size++;
            return n;
        }

        PLLNode<T>* insert_after(PLLNode<T>* node, T* data) {
            PLLNode<T>* n = new PLLNode<T>(node, node->next, data);
            node->next = n;
            if (n->next) { n->next->prev = n; }
            else { tail = n; }
            current_size++;
            return n;
        }

        PLLNode<T>* insert_before(PLLNode<T>* node, T* data) {
            PLLNode<T>* n = new PLLNode<T>(data);
            n->next = node;
            if (node->prev) {
                n->prev = node->prev;
                node->prev->next = n;
            }
            else {
                head = n;
            }
            node->prev = n;
            current_size++;
            return n;
        }

        void pop_back() {
            if (tail) {
                PLLNode<T>* temp = tail->prev;
                delete tail;
                tail = temp;
                if (tail == nullptr) { head = nullptr; }
                current_size--;
            }
        }

        void remove(PLLNode<T>* node) {
            // this will be the case a lot in sprite renderer
            if (node->prev) { node->prev->next = node->next; }
            else { head = node->next; }

            if (node->next) { node->next->prev = node->prev; }
            else { tail = node->prev; }

            delete node;
            current_size--;
        }

        void clear() {
            PLLNode<T>* current = head;
            while (current) {
                PLLNode<T>* temp = current->next;
                delete current;
                current = temp;
            }
        }

        PLLNode<T>* getHead() const { return head; }
        PLLNode<T>* getTail() const { return tail; }

        unsigned int size() const { return current_size; }
    
    private:    
        PLLNode<T>* head;
        PLLNode<T>* tail;
        unsigned int current_size;
    };

}
