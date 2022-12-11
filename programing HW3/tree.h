#pragma once
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include "stack.h"
#include "queue.h"
using namespace std;

template <class T> class tree_node {
    private:
        T data;
        tree_node<T> *left, *right;

    public:
        tree_node(): data(0), left(nullptr), right(nullptr) {}
        tree_node(T a): data(a), left(nullptr), right(nullptr) {}

        friend class binary_tree;
};

class binary_tree {
    private: 
        tree_node<char> *root;
        
        uint32_t isp(const char c) {
            if(c == '(') return 0;
            if(c == ')') return 19;
            if(c == '*' || c == '/') return 13;
            if(c == '+' || c == '-') return 12;
            return 0;
        }

        uint32_t icp(const char c) {
            if(c == '(') return 20;
            if(c == ')') return 1;
            if(c == '*' || c == '/') return 13;
            if(c == '+' || c == '-') return 12;
            return 0;
        }

        string _prefix(tree_node<char> *cur_node, string &s) {
            if(cur_node == nullptr) return "";
            s += cur_node->data;
            _prefix(cur_node->left, s);
            _prefix(cur_node->right, s);
            return s;
        }

        string _postfix(tree_node<char> *cur_node, string &s) {
            if(cur_node == nullptr) return "";
            _postfix(cur_node->left, s);
            _postfix(cur_node->right, s);
            s += cur_node->data;
            return s;
        }

        double _count(tree_node<char> *cur_node) {
            if(isdigit(cur_node->data)) return (double)(cur_node->data - '0');
            double l = _count(cur_node->left), r = _count(cur_node->right);
            if(cur_node->data == '+') return l + r;
            if(cur_node->data == '-') return l - r;
            if(cur_node->data == '*') return l * r;
            if(cur_node->data == '/') return l / r;
            return 0.0;
        }

        void free_tree(tree_node<char> *cur_node) {
            if(!cur_node) return;
            free_tree(cur_node->left);
            free_tree(cur_node->right);
            delete cur_node;
        }

    public:

        binary_tree(string &s) {
            stack<tree_node<char>*> stN;
            stack<char> stC;
            s = '(' + s + ')';
            for(int i = 0; i < s.length(); i++) {
                if(isdigit(s[i])) {
                    tree_node<char> *new_node = new tree_node<char>(s[i]);
                    stN.push(new_node);
                }
                else {
                    while(!stC.empty() && isp(stC.top()) >= icp(s[i])) {
                        tree_node<char> *new_node = new tree_node<char>(stC.top()); stC.pop();
                        new_node->right = stN.top(); stN.pop();
                        new_node->left = stN.top(); stN.pop();
                        stN.push(new_node);
                    }
                    if(s[i] == ')') {
                        stC.pop();
                    }
                    else {
                        stC.push(s[i]);
                    }
                }
            }
            root = stN.top(); stN.pop();
        }

        ~binary_tree() {
            free_tree(root);
        }
        
        string prefix() {
            string prefix = "";
            _prefix(root, prefix);
            return prefix;
        }

        string postfix() {
            string postfix = "";
            _postfix(root, postfix);
            return postfix;
        }

        string level_order() {
            if(root == nullptr) return "";
            string order = "";
            queue<tree_node<char>*> q(root);
            while(!q.empty()) {
                size_t size = q.size();
                while(size--) {
                    tree_node<char> *top = q.front();
                    order += top->data;
                    q.pop();
                    if(top->left != nullptr) q.push(top->left);
                    if(top->right != nullptr) q.push(top->right);
                }
            }
            return order;
        }

        double count() {
            return _count(root);
        }
};
