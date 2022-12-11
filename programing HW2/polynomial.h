#pragma once

#include <iostream>

using namespace std;

class term {
    public:
        double coef;
        int64_t power;

        term(double i_coef, int64_t i_power): coef(i_coef), power(i_power){}
};

class Node{
    private:
        term data;
        Node *next;
        Node *prev;
        friend class polynomial;
    
    public:
        Node(): data(term(0.0, 0)), next(nullptr), prev(nullptr) {}

        Node(term i_term): data(i_term), next(nullptr), prev(nullptr) {}

        term get() { return data; }
};

class polynomial {
    private:
        string name;
        Node dummy_head;
        uint64_t size;
        friend class polynomial;

        void __insert(Node *prev_node, term add_data){
            Node *new_node = new Node(add_data);
            Node *next_node = prev_node->next;
            prev_node->next = new_node;
            new_node->prev = prev_node;
            new_node->next = next_node;
            next_node->prev = new_node;
            size++;
        }

        void __erase(Node *cur_node) {
            Node *prev_node = cur_node->prev;
            Node *next_node = cur_node->next;
            prev_node->next = next_node;
            next_node->prev = prev_node;
            delete cur_node;
            size--;
        }

    public:
        polynomial() {
            name = "";
            dummy_head.next = &dummy_head;
            dummy_head.prev = &dummy_head;
            dummy_head.data.power = -1;
            size = 0;
        }

        polynomial(string i_name) {
            name = i_name;
            dummy_head.next = &dummy_head;
            dummy_head.prev = &dummy_head;
            dummy_head.data.power = -1;
            size = 0;
        }

        polynomial(polynomial &copy) {
            dummy_head.next = &dummy_head;
            dummy_head.prev = &dummy_head;
            dummy_head.data.power = -1;
            size = 0;
            Node* cur_node = copy.dummy_head.next;
            for(int i = 0; i < copy.size; i++) {
                __insert(dummy_head.prev, term(cur_node->data.coef, cur_node->data.power));
                cur_node = cur_node->next;
            }
        }

        ~polynomial(){
            for(int i = 0; i < this->size; i++) {
                __erase(this->dummy_head.next);
            }
        }

        uint64_t get_size() { return size; }

        string get_name() { return name; }
        void set_name(string i_name) {
            name = i_name;
        }

        void insert_term(double coef, int64_t power) {
            Node *cur_node = dummy_head.next;
            uint64_t idx = 1;
            while(cur_node->data.power > power && idx <= size) {
                cur_node = cur_node->next;
                idx++;
            }
            if(cur_node->data.power == power) {
                cur_node->data.coef += coef;
            }
            else {
                __insert(cur_node->prev, term(coef, power));
            }
        }

        void erase(int64_t power) {
            Node *cur_node = dummy_head.next;
            uint64_t idx = 1;
            while(cur_node->data.power != power && idx <= size) {
                cur_node = cur_node->next;
                idx++;
            }
            if(idx != size + 1) {
                __erase(cur_node);
            }
        }

        void show() {
            system("clear");
            Node *cur_node = dummy_head.next;
            cout<<name<<":"<<endl;
            bool flag = false;
            for(int i = 1; i <= size; i++ ) {
                if(cur_node->data.coef == 0) continue;
                if(i != 1 && cur_node->data.coef > 0) cout<<" +";
                if(cur_node->data.coef < 0) cout<<" ";
                if(cur_node->data.power != 0 && cur_node->data.coef != 1) cout<<cur_node->data.coef;
                if(cur_node->data.power == 0) cout<<cur_node->data.coef;
                if(cur_node->data.power != 0) cout<<"X";
                if(cur_node->data.power != 0 && cur_node->data.power != 1) cout<<"^"<<cur_node->data.power;
                cur_node = cur_node->next;
                flag = true;
            }
            if(!flag)  {
                cout<<0;
            }
            cout<<endl<<"---------------------------------------------------"<<endl;
        }

        double find_term_coef(int power) {
            Node *cur_node = dummy_head.next;
            for(int i = 0 ; i < this->size; i++) {
                if(power == cur_node->data.power) {
                    return cur_node->data.coef;
                }
                cur_node = cur_node->next;
            }
            return 0.0;
        }

        void operator +(const polynomial &that) {
            polynomial ans_pol("plus_pol");
            Node *cur_node1 = this->dummy_head.next, *cur_node2 = that.dummy_head.next;
            uint64_t size1 = this->size, size2 = that.size;
            while(size1 || size2) {
                if(cur_node1->data.power == cur_node2->data.power) {
                    if(cur_node1->data.coef + cur_node2->data.coef != 0) {
                        ans_pol.__insert(ans_pol.dummy_head.prev, term(cur_node1->data.coef + cur_node2->data.coef, cur_node1->data.power));
                    }
                    cur_node1 = cur_node1->next;
                    cur_node2 = cur_node2->next;
                    size1--;
                    size2--;
                }
                else if(cur_node1->data.power > cur_node2->data.power) {
                    ans_pol.__insert(ans_pol.dummy_head.prev, term(cur_node1->data.coef, cur_node1->data.power));
                    cur_node1 = cur_node1->next;
                    size1--;
                }
                else {
                    ans_pol.__insert(ans_pol.dummy_head.prev, term(cur_node2->data.coef, cur_node2->data.power));
                    cur_node2 = cur_node2->next;
                    size2--;
                }
            }
            ans_pol.show();
        }

        void operator -(const polynomial &that) {
            polynomial ans_pol("minus_pol");
            Node *cur_node1 = this->dummy_head.next, *cur_node2 = that.dummy_head.next;
            uint64_t size1 = this->size, size2 = that.size;
            while(size1 || size2) {
                if(cur_node1->data.power == cur_node2->data.power) {
                    if(cur_node1->data.coef - cur_node2->data.coef != 0) {
                        ans_pol.__insert(ans_pol.dummy_head.prev, term(cur_node1->data.coef + cur_node2->data.coef, cur_node1->data.power));
                    }
                    cur_node1 = cur_node1->next;
                    cur_node2 = cur_node2->next;
                    size1--;
                    size2--;
                }
                else if(cur_node1->data.power > cur_node2->data.power) {
                    ans_pol.__insert(ans_pol.dummy_head.prev, term(cur_node1->data.coef, cur_node1->data.power));
                    cur_node1 = cur_node1->next;
                    size1--;
                }
                else {
                    ans_pol.__insert(ans_pol.dummy_head.prev, term(-cur_node2->data.coef, cur_node2->data.power));
                    cur_node2 = cur_node2->next;
                    size2--;
                }
            }
            ans_pol.show();
        }

        void operator *(const polynomial &that) {
            polynomial ans_pol("multipile polynomail");
            Node *cur_node1 = this->dummy_head.next, *cur_node2 = that.dummy_head.next;
            uint64_t size1 = this->size, size2 = that.size;
            for(int i = 0; i < size1; i++) {
                for(int j = 0; j < size2; j++) {
                    ans_pol.insert_term(cur_node1->data.coef * cur_node2->data.coef, cur_node1->data.power + cur_node2->data.power);
                    cur_node2 = cur_node2->next;
                }
                cur_node1 = cur_node1->next;
                cur_node2 = cur_node2->next;
            }
            ans_pol.show();
        }

        void operator /(const polynomial &that) {
            polynomial ans_pol("divide polynomail");
            polynomial copy_pol(*this);
            copy_pol.set_name("remainder polynomail");
            Node *cur_node1 = copy_pol.dummy_head.next, *cur_node2 = that.dummy_head.next;
            double pol2_highest_term_power = that.dummy_head.next->data.power;
            double pol2_highest_term_coef = that.dummy_head.next->data.coef;
            uint64_t size1 = copy_pol.size, size2 = that.size;
            while(cur_node1->data.power >= pol2_highest_term_power) {
                double times = cur_node1->data.coef / pol2_highest_term_coef;
                int64_t p = cur_node1->data.power - pol2_highest_term_power;
                ans_pol.__insert(ans_pol.dummy_head.prev, term(times, p));
                for(int i = 0; i < size2; i++) {
                    copy_pol.insert_term((-1) * cur_node2->data.coef * times, cur_node2->data.power + p);
                    cur_node2 = cur_node2->next;
                }
                cur_node1 = cur_node1->next;
            }
            ans_pol.show();
            cout<<"Press enter to continue."<<endl;
            cin.ignore();
            getchar();
            copy_pol.show();
        }

};