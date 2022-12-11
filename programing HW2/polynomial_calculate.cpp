#include <iostream>
#include "polynomial.h"
#include "polynomial_calculate_lib.h"
using namespace std;

polynomial all_polynomial[105];
int64_t numbers_of_polynomial = 0;

int main() {
    while(1) {
        int64_t choose;
        hello();        
        cin>>choose;
        system("clear");
        if(choose == 1) {
            if(numbers_of_polynomial > 99) {
                cout<<"This program only support 100 polynomial."<<endl;
                wait();
            }
            polynomial &cur_pol = all_polynomial[numbers_of_polynomial];
            string name;
            double coef;
            int64_t power;
            while(1) {
                cout<<"Please input polnamial name: ";
                cin>>name;
                if(check_same_name(name)) continue;
                cur_pol.set_name(name);
                break;
            }
            while(1) {
                cur_pol.show();
                cout<<"Please input power(input negative number to stop): ";
                cin>>power;
                if(power < 0) {
                    if(cur_pol.get_size() == 0) {
                        cout<<"Your polnomial has to have one term at least."<<endl;
                        wait();
                        system("clear");
                        continue;
                    }
                    break;
                }
                if(cur_pol.find_term_coef(power) != 0.0) {
                    cout<<"You have inputed this term!"<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                cout<<"Please input coefficient: ";
                cin>>coef;
                if(coef == 0.0) {
                    cout<<"You can't input the 0 term"<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                cur_pol.insert_term(coef, power);
            }
            numbers_of_polynomial++;
        }
        else if(choose == 2) {
            if(numbers_of_polynomial < 1) {
                cout<<"Please add more new polnomial first."<<endl;
                continue;
            }
            int64_t idx = find_polynomial("show");
            if(idx == -1) {
                wait();
                system("clear");
                continue;
            }
            polynomial &cur_pol = all_polynomial[idx];
            cur_pol.show();
        }
        else if(choose == 3) {
            if(numbers_of_polynomial < 1) {
                cout<<"Please add more new polnomial first."<<endl;
                continue;
            }
            int64_t idx = find_polynomial("show the coefficient");
            if(idx == -1) {
                continue;
            }
            polynomial &cur_pol = all_polynomial[idx];
            int64_t power;
            double coef;
            while(1) {
                cur_pol.show();
                cout<<"Please input the term of the power which coefficient you want to show: ";
                cin>>power;
                coef = cur_pol.find_term_coef(power);
                if(coef == 0.0) {
                    cout<<"Can't find this term!"<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                break;
            }
            cout<<"The coef is "<<coef<<"."<<endl;
        }
        else if(choose == 4) {
            if(numbers_of_polynomial < 1) {
                cout<<"Please add more new polnomial first."<<endl;
                continue;
            }
            int64_t idx = find_polynomial("add term");
            if(idx == -1) {
                continue;
            }
            polynomial &cur_pol = all_polynomial[idx];
            int64_t power;
            double coef;
            while(1) {
                cur_pol.show();
                cout<<"Please input power: ";
                cin>>power;
                if(power < 0.0) {
                    cout<<"Power can't less than 0."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                if(cur_pol.find_term_coef(power) != 0.0) {
                    cout<<"You have inputed this term."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                cout<<"Please input coefficient: ";
                cin>>coef;
                if(coef == 0.0) {
                    cout<<"You can't input the 0 term."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                break;
            }
            cur_pol.insert_term(coef, power);
            cur_pol.show();
        }
        else if(choose == 5) {
            if(numbers_of_polynomial < 1) {
                cout<<"Please add more new polnomial first."<<endl;
                continue;
            }
            int64_t idx = find_polynomial("erase term");
            if(idx == -1) {
                continue;
            }
            polynomial &cur_pol = all_polynomial[idx];
            if(cur_pol.get_size() == 1) {
                cout<<"This polnomial only has one term, you can't remove it."<<endl;
                continue;
            }
            int64_t power;
            while(1) {
                cur_pol.show();
                cout<<"Please input power of term you want to earse: ";
                cin>>power;
                if(power < 0.0) {
                    cout<<"Power can't less than 0."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                if(cur_pol.find_term_coef(power) == 0.0) {
                    cout<<"You can't erase the term which doesn't exist."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                break;
            }
            cur_pol.erase(power);
            cur_pol.show();
        }
        else if(choose == 6) {
            if(numbers_of_polynomial < 1) {
                cout<<"Please add more new polnomial first."<<endl;
                continue;
            }
            int64_t idx1 = find_polynomial("first polnomial to be plused");
            if(idx1 == -1) {
                continue;
            }
            int64_t idx2 = find_polynomial("second polnomial to plus");
            if(idx2 == -1) {
                continue;
            }
            polynomial &pol1 = all_polynomial[idx1];
            polynomial &pol2 = all_polynomial[idx2];
            pol1 + pol2;
        }
        else if(choose == 7) {
            if(numbers_of_polynomial < 1) {
                cout<<"Please add more new polnomial first."<<endl;
                continue;
            }
            int64_t idx1 = find_polynomial("first polnomial to be minus");
            if(idx1 == -1) {
                continue;
            }
            int64_t idx2 = find_polynomial("second polnomial to minus");
            if(idx2 == -1) {
                continue;
            }
            polynomial &pol1 = all_polynomial[idx1];
            polynomial &pol2 = all_polynomial[idx2];
            pol1 - pol2;
        }
        else if(choose == 8) {
            if(numbers_of_polynomial < 1) {
                cout<<"Please add more new polnomial first."<<endl;
                continue;
            }
            int64_t idx1 = find_polynomial("first polnomial to be multiplied");
            if(idx1 == -1) {
                wait();
                system("clear");
                continue;
            }
            int64_t idx2 = find_polynomial("second polnomial to multiply");
            if(idx2 == -1) {
                continue;
            }
            polynomial &pol1 = all_polynomial[idx1];
            polynomial &pol2 = all_polynomial[idx2];
            pol1 * pol2;
        }
        else if(choose == 9) {
            if(numbers_of_polynomial < 1) {
                cout<<"Please add more new polnomial first."<<endl;
                continue;
            }
            int64_t idx1 = find_polynomial("first polnomial to be divided");
            if(idx1 == -1) {
                continue;
            }
            int64_t idx2 = find_polynomial("second polnomial to divide");
            if(idx2 == -1) {
                continue;
            }
            polynomial &pol1 = all_polynomial[idx1];
            polynomial &pol2 = all_polynomial[idx2];
            pol1 / pol2;
        }
        else if(choose == 10) {
            cout<<"EXIT."<<endl;
            wait();
            system("clear");
            exit(0);
        }
        else {
            cout<<"EXIT."<<endl;
            wait();
            system("clear");
            exit(0);
        }
        wait();
    }
}