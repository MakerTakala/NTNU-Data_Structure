#pragma once
#include <stdlib.h>
#include "list.h"

template<class T> class queue {
    private:
        size_t _size;
        list<T> _data;
    public:
        queue() {
            _size = 0;
        }

        queue(T &root) {
            _size = 0;
            this->push(root);
        }

        T& front() {
            return _data.front();
        }

        T& back() {
            return _data.back();
        }

        size_t size() {
            return _size;
        }

        bool empty() {
            return _size == 0;
        }
        
        void push(const T &x) {
            _data.push_back(x);
            _size++;
        }

        void pop() {
            _data.pop_front();
            _size--;
        }
};