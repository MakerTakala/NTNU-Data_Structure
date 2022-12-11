#pragma once
#include <stdlib.h>
#include <iostream>


template <class T> class list_node {
    private:
        T data;
        list_node *next;
        list_node *prev;

    public:
        list_node(): data(0), next(nullptr), prev(nullptr) {}
        list_node(const T &a): data(a), next(nullptr), prev(nullptr) {}
        template<typename U>friend class list;
};

template <class T> class list {
    private:
        list_node<T> _dummy_head;
        size_t _size; 

        void insert(list_node<T> *prev_node, const T &data) {
            list_node<T> *new_node = new list_node<T>(data);
            list_node<T> *next_node = prev_node->next;
            prev_node->next = new_node;
            new_node->prev = prev_node;
            new_node->next = next_node;
            next_node->prev = new_node;
            _size++;
        }

        void erase(list_node<T> *cur_node) {
            list_node<T> *prev_node = cur_node->prev;
            list_node<T> *next_node = cur_node->next;
            prev_node->next = next_node;
            next_node->prev = prev_node;
            delete cur_node;
            _size--;
        }

    public:
        list() {
            _dummy_head.prev = &_dummy_head;
            _dummy_head.next = &_dummy_head;
            _size = 0;
        }

        ~list() {
            while(this->_size) {
                erase(this->_dummy_head.next);
            }
        }

        T& back() {
            return _dummy_head.prev->data;
        }

        T& front() {
            return _dummy_head.next->data;
        }

        size_t size() {
            return _size;
        }

        bool empty() {
            return _size == 0;
        }
        
        void push_back(const T &data) {
            insert(_dummy_head.prev, data);
        }

        void pop_back() {
            erase(_dummy_head.prev);
        }

        void push_front(const T &data) {
            insert(&_dummy_head, data);
        }

        void pop_front() {
            erase(_dummy_head.next);
        }

};