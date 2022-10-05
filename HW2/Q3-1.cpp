#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_degree 101 /*MAX degree of polynomial+1*/ 

typedef struct{
    int degree;
    int coef [MAX_degree]; 
}polynomial;

int coeff1(polynomial a, int p) {
    if(p > MAX_degree - 1) return 0;
    return a.coef[p];
}

void init_polynomial(polynomial &a) {
    for (int i = 0 ; i < MAX_degree; i++){
        a.coef[i] = 0;
    }
    a.degree = 0;
}

int add_polynomial(polynomial &a, int degree, int coef) {
    if(coef > MAX_degree - 1) return 0;
    a.coef[degree] = coef;
    a.degree = max(a.degree, degree);
    return 1;
}

int main() {
    polynomial poly;
    init_polynomial(poly);
    add_polynomial(poly, 0, 10);
    add_polynomial(poly, 5, 20);
    add_polynomial(poly, 10, 30);
    add_polynomial(poly, 15, 40);

    cout<<"power 0 's cofficient = "<<coeff1(poly, 0)<<endl;
    cout<<"power 5 's cofficient = "<<coeff1(poly, 5)<<endl;
    cout<<"power 10 's cofficient = "<<coeff1(poly, 10)<<endl;
    cout<<"power 15 's cofficient = "<<coeff1(poly, 15)<<endl;

    return 0;
}