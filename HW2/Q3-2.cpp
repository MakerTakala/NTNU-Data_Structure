#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_TERMS 100 /*size of terms array*/

typedef struct{
    float coef;
    int expon; 
}polynomial;

int coeff2(polynomial a[], int avail, int p) {
    for(int i = 0; i < avail; i++) {
        if(a[i].expon == p) {
            return a[i].coef;
        }
    }
    return 0;
}

void init_polynomial(polynomial a[], int &avail) {
    for(int i = 0; i < MAX_TERMS; i++) {
        a[i].coef = 0;
        a[i].expon = 0;
    }
    avail = 0;
}

int add_polynomial(polynomial a[], int &avail, int coef, int expon) {
    if(expon > MAX_TERMS) return 0;
    int i;
    for(i = avail - 1; i >= 0; i--) {
        if(expon > a[i].expon) {
            break;
        }
        swap(a[i], a[i + 1]);
    }
    a[i + 1].coef = coef;
    a[i + 1].expon = expon;
    avail++;
    return 1;
}

int main() {
    polynomial terms[MAX_TERMS];
    int avail = 0;
    init_polynomial(terms, avail);
    add_polynomial(terms, avail, 10, 0);
    add_polynomial(terms, avail, 20, 5);
    add_polynomial(terms, avail, 30, 10);
    add_polynomial(terms, avail, 40, 15);

    cout<<"power 0 's cofficient = "<<coeff2(terms, avail, 0)<<endl;
    cout<<"power 5 's cofficient = "<<coeff2(terms, avail, 5)<<endl;
    cout<<"power 10 's cofficient = "<<coeff2(terms, avail, 10)<<endl;
    cout<<"power 15 's cofficient = "<<coeff2(terms, avail, 15)<<endl;

    return 0;
}