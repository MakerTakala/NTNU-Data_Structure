#include "matrix_calculate_lib.h"

extern sparse_matrix all_sparse_matrix[100];
extern int64_t numbers_of_sparse_martix;

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
    cout<<"1. Add new matrix"<<endl;
    cout<<"2. Display martrix"<<endl;
    cout<<"3. Display submatrix"<<endl;
    cout<<"4. Display transform matrix"<<endl;
    cout<<"5. Element-wise produce"<<endl;
    cout<<"6. Matrix multiplication"<<endl;
    cout<<"7. square quickly multiplication"<<endl;
    cout<<"8. EXIT"<<endl;
    cout<<"Please choose your operation with number(1-8): "; 
}

bool matrix_amount_less(int64_t num) {
    if(numbers_of_sparse_martix < num) {
        cout<<"Please add more new matrix first."<<endl;
        wait();
        return false;
    }
    return true;
}

void show_matrix(sparse_matrix matrix) {
    system("clear");
    cout<<matrix.name()<<":"<<endl;
    cout<<"    row: "<<matrix.row()<<endl;
    cout<<"    col: "<<matrix.col()<<endl;
    
    int64_t get_data[MAX_ROW + 1][MAX_COL + 1] = {{0}};
    int64_t digit = matrix.get_data(get_data);
    digit = log10(digit == 0 ? 1 : digit) + 2;
    cout<<endl;
    for(int i = 0; i <= digit ; i++) cout<<" ";
    cout<<"|";
    for(int i = 1; i <= matrix.col(); i++) cout<<setw(digit)<<i<<" ";
    cout<<endl; 
    for(int i = 0; i <= digit; i++) cout<<"-";
    for(int i = 0; i <= (matrix.col() * (digit + 1)); i++) cout<<"-";
    cout<<endl;

    for(int i = 0; i < matrix.row(); i++) {
        cout<<setw(digit)<<i + 1<<" |";
        for(int j = 0; j < matrix.col(); j++)  {
            cout<<setw(digit)<<get_data[i][j]<<" ";
        }
        cout<<endl;
    }
    print_line();
}

sparse_matrix find_sparse_matrix(const char say[]) {
    char name[1024] = {0};
    while(1) {
        system("clear");
        cout<<"Matrix list:"<<endl;
        for(int i = 0; i < numbers_of_sparse_martix; i++) {
            cout<<"    "<<all_sparse_matrix[i].name()<<endl;
        }
        cout<<endl<<"Please input matrix name for "<<say<<endl<<"(enter \"0\" will stop this operation): ";
        cin>>name;
        if(!strcmp(name, "0")) break;;
        for(int i = 0; i < numbers_of_sparse_martix; i++) {
            if(!strcmp(all_sparse_matrix[i].name(), name)) {
                system("clear");
                cout<<name<<":"<<endl;
                return all_sparse_matrix[i];
            }
        }
        cout<<"Can't find correspond matrix name.";
    }
    return sparse_matrix();
}

bool check_same_name(char name[]) {
    for(int i = 0; i < numbers_of_sparse_martix; i++) {
        if(!strcmp(all_sparse_matrix[i].name(), name)) {
            cout<<"This name has been use."<<endl;
            wait();
            system("clear");
            return true;
        }
    }
    return false;
}

void save_matrix(sparse_matrix &matrix) {
    char name[1024];
    while(1) {
        cout<<"If you want to save this matrix, input 'Y' to save, or input 'N' to leave: ";
        fflush(stdin);
        char c = getchar();
        if(c == 'Y') {
            while(1) {
                system("clear");
                show_matrix(matrix);
                cout<<"Please enter matrix's name: ";
                cin>>name;
                if(check_same_name(name)) continue;
                break;
            }
            matrix.set_name(name);
            all_sparse_matrix[numbers_of_sparse_martix] = sparse_matrix(matrix);
            numbers_of_sparse_martix++;
            show_matrix(matrix);
            cout<<"Matrix "<<name<<" has been saved."<<endl;
            break;
        }
        else if(c == 'N') {
            break;
        }
    }
}