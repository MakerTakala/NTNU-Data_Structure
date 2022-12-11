# include <iostream>
#include <sstream>
#include <string>
#include "list.h"
using namespace std;

list<int> rings[30];
list<int> untie_rings[30];
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

void get_component_for_untie_rings(int cur_node) {
    visited[cur_node] = 1;
    list_node<int> *next_node = untie_rings[cur_node]._dummy_head.next;
    for(int i = 0; i < untie_rings[cur_node].size(); i++) {
        if(visited[next_node->data] == 0) {
            get_component_for_untie_rings(next_node->data);
        }
        next_node = next_node->next;
    }
}

bool detect_cycle_for_untie_rings(int parent_node, int cur_node) {
    visited[cur_node] = 1;
    list_node<int> *next_node = untie_rings[cur_node]._dummy_head.next;
    bool is_cycle = false;
    for(int i = 0; i < untie_rings[cur_node].size(); i++) {
        if(visited[next_node->data] == 1 && next_node->data != parent_node) is_cycle = true;
        if(visited[next_node->data] == 0) {
            is_cycle |= detect_cycle_for_untie_rings(cur_node, next_node->data);
        }
        next_node = next_node->next;
    }
    return is_cycle;
}


int main() {
    
    //read ring connect situation
    cin>>n>>m;
    for(int i = 0, a, b; i < m; i++) {
        cin>>a>>b;
        if(a != b) {
            rings[a].push_back(b);
            rings[b].push_back(a);
            untie_rings[a].push_back(b);
            untie_rings[b].push_back(a);
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, untie_string);
    stringstream ss;
    ss<<untie_string;
    while(1) {
        ss >> untie_nodes[untie_nodes_size++];
        if(ss.fail()) break;
    }

    //erase untie
    for(int i = 0; i < untie_nodes_size; i++) {
        int cur_erase_number = untie_nodes[i];
        list_node<int> *cur_node = untie_rings[cur_erase_number]._dummy_head.next;
        for(int i = 0; i < untie_rings[cur_erase_number].size(); i++) {
            untie_rings[cur_node->data].erase_val(cur_erase_number);
            cur_node = cur_node->next;
        }
        untie_rings[cur_erase_number].clear();
    }

    //detect legel
    bool is_chain = true;
    for(int i = 1; i <= n; i++) {
        if(untie_rings[i].size() > 2) is_chain = false;
    }
    fill(visited, visited + 30, 0);
    for(int i = 1; i <= n; i++) {
        if(visited[i] == 0 && detect_cycle_for_untie_rings(-1, i)) {
            is_chain = false;
        }
    }
    int untie_conponent = 0;
    fill(visited, visited + 30, 0);
    for(int i = 1; i <= n; i++) {
        if(visited[i] == 0) {
            untie_conponent++;
            get_component_for_untie_rings(i);
        }
    }
    if(untie_nodes_size < (untie_conponent - untie_nodes_size - 1))  is_chain = false;
    cout<<(is_chain ? "YES" : "No")<<endl;




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