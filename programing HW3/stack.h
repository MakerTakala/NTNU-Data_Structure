#pragma once
#include <stdlib.h>
#include "list.h"

template<class T> class stack {
    private:
        size_t _size;
        list<T> _data;
    public:
        stack() {
            _size = 0;
        }

        T& top() {
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
            _data.pop_back();
            _size--;
        }
};
