# include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>
#include "list.h"
using namespace std;

list<int> rings[30];
list<int> test_rings[30];
int visited[30];
int n, m;

void get_component_for_rings(int cur_node) {
    visited[cur_node] = 1;
    list_node<int> *next_node = rings[cur_node]._dummy_head.next;
    for(int i = 0; i < rings[cur_node].size(); i++) {
        if(visited[next_node->data] == 0) {
            get_component_for_rings(next_node->data);
        }
        next_node = next_node->next;
    }
}

void get_component_for_test_rings(int cur_node) {
    visited[cur_node] = 1;
    list_node<int> *next_node = test_rings[cur_node]._dummy_head.next;
    for(int i = 0; i < test_rings[cur_node].size(); i++) {
        if(visited[next_node->data] == 0) {
            get_component_for_test_rings(next_node->data);
        }
        next_node = next_node->next;
    }
}

bool detect_cycle_for_test_rings(int parent_node, int cur_node) {
    visited[cur_node] = 1;
    list_node<int> *next_node = test_rings[cur_node]._dummy_head.next;
    bool is_cycle = false;
    for(int i = 0; i < test_rings[cur_node].size(); i++) {
        if(visited[next_node->data] == 1 && next_node->data != parent_node) is_cycle = true;
        if(visited[next_node->data] == 0) {
            is_cycle |= detect_cycle_for_test_rings(cur_node, next_node->data);
        }
        next_node = next_node->next;
    }
    return is_cycle;
}

void copy_chain() {
    for(int i = 1; i <= n; i++) {
        test_rings[i].clear();
        list_node<int>* cur_node = rings[i]._dummy_head.next;
        for(int j = 0; j < rings[i].size(); j++) {
            test_rings[i].push_back(cur_node->data);
            cur_node = cur_node->next;
        }
    }
}

bool test_chain(int untie[], size_t size) {
    copy_chain();

    //erase untie
    for(int i = 0; i < size; i++) {
        int cur_erase_number = untie[i];
        list_node<int> *cur_node = test_rings[cur_erase_number]._dummy_head.next;
        for(int i = 0; i < test_rings[cur_erase_number].size(); i++) {
            test_rings[cur_node->data].erase_val(cur_erase_number);
            cur_node = cur_node->next;
        }
        test_rings[cur_erase_number].clear();
    }

    //detect
    bool is_chain = true;
    for(int i = 1; i <= n; i++) {
        if(test_rings[i].size() > 2) is_chain = false;
    }
    fill(visited, visited + 30, 0);
    for(int i = 1; i <= n; i++) {
        if(visited[i] == 0 && detect_cycle_for_test_rings(-1, i)) {
            is_chain = false;
        }
    }
    
    int conponent = 0;
    fill(visited, visited + 30, 0);
    for(int i = 1; i <= n; i++) {
        if(visited[i] == 0) {
            conponent++;
            get_component_for_test_rings(i);
        }
    }
    if(size < (conponent - size - 1))  is_chain = false;
    return is_chain;
}

bool search_conbination(int target, int choose[], int size, int cur) {
    if(target == size) {
        return test_chain(choose, size);
    }
    bool flag = false;
    for(int i = cur + 1; i < n; i++) {
        choose[size++] = i;
        flag |= search_conbination(target, choose, size, i);
        size--;
    }
    return flag;
}

int main() {
    
    fstream in;
    in.open("test2.txt");

    //read ring connect situation
    in>>n>>m;
    for(int i = 0, a, b; i < m; i++) {
        in>>a>>b;
        if(a != b) {
            rings[a].push_back(b);
            rings[b].push_back(a);
        }
    }
    
    //count the component
    int conponent = 0;
    fill(visited, visited + 30, 0);
    for(int i = 1; i <= n; i++) {
        if(visited[i] == 0) {
            conponent++;
            get_component_for_rings(i);
        }
    }
    cout<<conponent<<endl;


    //read untie rings
    int untie_nodes[30] = {0};
    int untie_nodes_size = 0;
    string untie_string;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(in, untie_string);
    stringstream ss;
    ss<<untie_string;
    while(1) {
        ss >> untie_nodes[untie_nodes_size];
        if(ss.fail()) break;
        untie_nodes_size++;
    }
    cout<<(test_chain(untie_nodes, untie_nodes_size) ? "YES" : "NO")<<endl;;


    int conbiantion[30] = {0};
    for(int i = 1; i <= n; i++) {
        if(search_conbination(i, conbiantion, 0, 0)) {
            cout<<i<<endl;
            break;
        }
    }

    in.close();

    return 0;
}

/*
5 3
1 2
2 3
4 5
1 2 3

7 7
1 2
2 3
3 1
4 5
5 6
6 7
7 4 
4 5 6 7
*/