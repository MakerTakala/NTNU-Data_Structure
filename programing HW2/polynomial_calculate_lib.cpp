#include "polynomial_calculate_lib.h"

extern polynomial all_polynomial[100];
extern int64_t numbers_of_polynomial;

void print_line() {
    cout<<endl<<"---------------------------------------------------"<<endl;
}

void wait() {
    cout<<"Press enter to continue."<<endl;
    cin.ignore();
    getchar();
}

void hello() {
    system("clear");
    cout<<"1. Add new polynomial"<<endl;
    cout<<"2. Display polynomial"<<endl;
    cout<<"3. Display indicate term's coefficient"<<endl;
    cout<<"4. Add new term"<<endl;
    cout<<"5. Remove the term"<<endl;
    cout<<"6. Add two polynomial"<<endl;
    cout<<"7. Subtract two polynomial"<<endl;
    cout<<"8. Multiply two polynomial"<<endl;
    cout<<"9. divided two polynomial"<<endl;
    cout<<"10. EXIT"<<endl;
    cout<<"Please choose your operation with number(1-10): "; 
}

int64_t find_polynomial(const string say) {
    string name;
    while(1) {
        system("clear");
        cout<<"Polynomial list:"<<endl;
        for(int i = 0; i < numbers_of_polynomial; i++) {
            cout<<"    "<<all_polynomial[i].get_name()<<endl;
        }
        cout<<endl<<"Please input polynomial name for "<<say<<":";
        cin>>name;
        for(int i = 0; i < numbers_of_polynomial; i++) {
            if(all_polynomial[i].get_name() == name) {
                return i;
            }
        }
        cout<<"Can't find correspond polynomial name."<<endl;
        wait();
        system("clear");
        continue;
    }
    return -1;
}

bool check_same_name(string name) {
    for(int i = 0; i < numbers_of_polynomial; i++) {
        if(all_polynomial[i].get_name() == name) {
            cout<<"This name has been use."<<endl;
            wait();
            system("clear");
            return true;
        }
    }
    return false;
}