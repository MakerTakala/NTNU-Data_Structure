#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include "tree.h"
using namespace std;

void wait() {
    cout<<"Press enter to continue."<<endl;
    cin.ignore();
    getchar();
}

bool check(string s) {
    int8_t parentheses = 0;
    bool state = false;
    for(int i = 0; i < s.length(); i++) {
        if(!isdigit(s[i]) && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '(' && s[i] != ')') return false;
        if(s[i] == '('){
            parentheses++;
            continue;
        }
        if(s[i] == ')'){
            parentheses--;
            continue;
        }
        if(parentheses < 0 ) return false;
        if((isdigit(s[i]) && state == true) || (!isdigit(s[i]) && state == false)) return false;
        state ^= true;
    }
    return parentheses == 0;
}
 
int main() {

    while(1) {
        system("clear");
        cout<<"Please enter an infix expression and press enter\n(enter esacpe key word will stop the program)\n: ";
        string input;
        cin>>input;
        if(input[0] == 27) break;
        if(!check(input)) {
            cout<<"This arithmetic is illegal."<<endl;
            wait();
            continue;
        }
        binary_tree bt(input);
        cout<<"The postfix expression: "<<bt.postfix()<<endl;
        cout<<"The prefix expression: "<<bt.prefix()<<endl;
        cout<<"The level order expression: "<<bt.level_order()<<endl;
        cout<<"="<<bt.count()<<endl;
        wait();
    }
    return 0;
}