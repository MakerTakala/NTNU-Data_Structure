// This is a file which collect all function and class in one

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

#define MAX_ROW 100
#define MAX_COL 100
#define MAX_ELEMENT 1000


void print_line();
void wait();
void hello();

typedef struct {
    int64_t row, col, num;
} element;

class spare_matrix {
private:
    int64_t data_row;
    int64_t data_col;
    string data_name;
    
    int64_t data_size;
    element data[MAX_ELEMENT + 1];

    void __set_name(string input_name) {
        data_name = input_name;
    }
    void __set_row(int64_t input_row) {
        data_row = input_row;
        data[0].row = input_row;
    }

    void __set_col(int64_t input_col) {
        data_col = input_col;
        data[0].col = input_col;
    }

    void __set_data(int64_t input_row, int64_t input_col, int64_t input_data) {
        data_size++;
        data[0].num++;
        data[data_size].row = input_row;
        data[data_size].col = input_col;
        data[data_size].num = input_data;
    }
    
    static bool data_cmp (element a, element b) {
        if(a.row == b.row) return a.col < b.col;
        return a.row < b.row;
    }
    
public:
    int64_t row() { return data_row; }
    int64_t col() { return data_col; }
    string name() { return data_name; }
    ino64_t size() { return data_size; }

    spare_matrix() {
        data_row = 0;
        data_col = 0;
        data_name = "";
        data_size = 0;
        for(int i = 0; i < MAX_ELEMENT; i++) {
            data[i].row = 0;
            data[i].col = 0;
            data[i].num = 0;
        }
    }

    spare_matrix(const spare_matrix &copy_spare_matrix) {
        data_row = copy_spare_matrix.data_row;
        data_col = copy_spare_matrix.data_col;
        data_name = copy_spare_matrix.data_name;
        data_size = copy_spare_matrix.data_size;
        for(int i = 0; i < MAX_ELEMENT; i++) {
            data[i].row = copy_spare_matrix.data[i].row;
            data[i].col = copy_spare_matrix.data[i].col;
            data[i].num = copy_spare_matrix.data[i].num;
        }
    }
    
    spare_matrix(const int64_t row, const int64_t col, const string name) {
        data_row = row;
        data[0].row = row;
        data_col = col;
        data[0].col = col;
        data_size = 0;
        data[0].num = 0;
        data_name = name;
        for(int i = 1; i < MAX_ELEMENT; i++) {
            data[i].row = 0;
            data[i].col = 0;
            data[i].num = 0;
        }
        
    }

    int set_name(string input_name) {
        __set_name(input_name);
        return 1;
    }

    int set_row(int64_t input_row) {
        if(input_row <= 0 || MAX_ROW < input_row) return 0;
        __set_row(input_row);
        return 1;
    }

    int set_col(int64_t input_col) {
        if(input_col <= 0 || MAX_COL < input_col) return 0;
        __set_col(input_col);
        return 1;
    }

    int set_data(int64_t input_row, int64_t  input_col, int64_t input_num) {
        if(input_row <= 0 || data_row < input_row || input_col <= 0 || data_col < input_col) {
            return 0;
        }
        __set_data(input_row, input_col, input_num);
        return 1;
    }

    spare_matrix sort_data() {
        sort(data + 1, data + 1 + data_size, data_cmp);
        return *this;
    }

    int64_t get_data(int64_t get_data[MAX_ROW + 1][MAX_ROW + 1]) {
        int64_t MAX = INT64_MIN;
        for(int i = 1 ; i <= data_size; i++) {
            get_data[data[i].row - 1][data[i].col - 1] = data[i].num;
            MAX = max(MAX, data[i].num);
        }
        return MAX;
    }

    spare_matrix sub_matrix(int64_t rows[], int64_t cols[], int64_t row_size, int64_t col_size) {
        spare_matrix this_matrix(row_size, col_size, "Submatrix_" + this->name());
        int64_t tmp_matrix[MAX_ROW + 1][MAX_COL + 1] = {{0}};

        for(int i = 1; i <= data_size; i++) {
            tmp_matrix[data[i].row][data[i].col] = data[i].num;
        }
        sort(rows, rows + row_size);
        sort(cols, cols + col_size);

        for(int i = 0; i < row_size; i++) {
            for(int j = 0; j < col_size; j++) {
                if(rows[i] <= 0 || data_row < rows[i] || cols[i] <= 0 || data_col < cols[i]) {
                    return spare_matrix();
                }
                if(tmp_matrix[rows[i]][cols[j]] != 0) {
                    this_matrix.set_data(i + 1, j + 1, tmp_matrix[rows[i]][cols[j]]);
                }
            }
        }
        return this_matrix;
    }

    spare_matrix transpose() {
        spare_matrix transpose_matrix(this->col(), this->row(), "Transpose_matrix_" + this->name());
        transpose_matrix.data_size = this->data_size;
        transpose_matrix.data[0].num = this->data_size;
        
        int64_t row_term[MAX_COL] = {0}, starting_pos[MAX_COL] = {0};
        for(int i = 1; i <= data_size; i++) {
            row_term[data[i].col]++;
        }
        starting_pos[0] = 1;
        for(int i = 1; i <= data_col; i++) {
            starting_pos[i] = starting_pos[i - 1] + row_term[i - 1];
        }
        for(int i = 1; i <= data_size; i++) {
            transpose_matrix.data[starting_pos[data[i].col]].row = data[i].col;
            transpose_matrix.data[starting_pos[data[i].col]].col = data[i].row;
            transpose_matrix.data[starting_pos[data[i].col]].num = data[i].num;
            starting_pos[data[i].col]++;
        }
        return transpose_matrix;
    }

    spare_matrix element_wise_product(spare_matrix input_matrix) {
        if(data_row != input_matrix.row() || data_col != input_matrix.col()) return spare_matrix();
        spare_matrix product_matrix(data_row, data_col, "Element_wise_Product_matrix_" + this->name() + "X" + input_matrix.name());
        int64_t first_pointer = 1, second_pointer = 1; 
        while(first_pointer <= data_size && second_pointer <= input_matrix.size()) {
            if(data[first_pointer].row == input_matrix.data[second_pointer].row && data[first_pointer].col == input_matrix.data[second_pointer].col) {
                product_matrix.set_data(data[first_pointer].row, data[first_pointer].col, data[first_pointer].num * input_matrix.data[second_pointer].num);
                first_pointer++;
                second_pointer++;
            }
            else {
                if(data[first_pointer].row == input_matrix.data[second_pointer].row) {
                    if(data[first_pointer].col < input_matrix.data[second_pointer].col) 
                        first_pointer++;
                    else 
                        second_pointer++;
                }
                else {
                    if(data[first_pointer].row < input_matrix.data[second_pointer].row) 
                        first_pointer++;
                    else 
                        second_pointer++;
                }
            }
        }
        return product_matrix;
    }

    spare_matrix multiplication(spare_matrix input_matrix) {
        if(data_col != input_matrix.row()) return spare_matrix();
        spare_matrix outer_product_matrix(data_row, input_matrix.col(), "multiplication_matrix_" + this->name() + "X" + input_matrix.name());
        
        input_matrix = input_matrix.transpose();
        int64_t a_idx = 1, b_idx = 1;
        int64_t a_row_begin = 1, b_row_begin = 1;
        int64_t sum = 0;

        while(a_idx <= data_size) {
            if(data[a_idx].col < input_matrix.data[b_idx].col) {
                ++a_idx;
            }
            else if(data[a_idx].col > input_matrix.data[b_idx].col) {
                ++b_idx;
            }
            else {
                sum += data[a_idx].num * input_matrix.data[b_idx].num;
                ++b_idx;
            }
            
            if(data[a_idx].row != data[a_row_begin].row) {
                a_idx = a_row_begin;
                ++b_idx;
            }
            
            if(input_matrix.data[b_idx].row != input_matrix.data[b_row_begin].row) {
                if(sum != 0) {
                    outer_product_matrix.set_data(data[a_row_begin].row, input_matrix.data[b_row_begin].row, sum);
                    sum = 0;
                }
                b_row_begin = b_idx;
                a_idx = a_row_begin;
            }

            if(b_idx > input_matrix.size()) {
                if(sum != 0) {
                    outer_product_matrix.set_data(data[a_row_begin].row, input_matrix.data[b_row_begin].row, sum);
                    sum = 0;
                }
                while(data[a_idx].row == data[a_row_begin].row) a_idx++;
                a_row_begin = a_idx;
                b_idx = 1;
                b_row_begin = 1;
            }
        }
        return outer_product_matrix;
    }

    spare_matrix square_multiplication(int64_t times) {
        if(data_row != data_col) return spare_matrix();
        if(times == 1) return spare_matrix(*this);
        spare_matrix exponentiation_matrix(square_multiplication(times / 2));
        if(times & 1) return spare_matrix(*this).multiplication(exponentiation_matrix.multiplication(exponentiation_matrix));
        else return exponentiation_matrix.multiplication(exponentiation_matrix);
    }
};

spare_matrix all_spare_matrix[100];
int64_t numbers_of_spare_martix = 0;

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
    cout<<"Please choose your operation with number(1-7): "; 
}

bool matrix_amount_less(int64_t num) {
    if(numbers_of_spare_martix < num) {
        cout<<"Please add more new matrix first."<<endl;
        wait();
        return false;
    }
    return true;
}

void show_matrix(spare_matrix matrix) {
    system("clear");
    cout<<matrix.name()<<":"<<endl;
    cout<<"    row: "<<matrix.row()<<endl;
    cout<<"    col: "<<matrix.col()<<endl;
    
    int64_t get_data[MAX_ROW + 1][MAX_COL + 1] = {{0}};
    int64_t digit = (int64_t)log10(matrix.get_data(get_data)) + 2;
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

spare_matrix find_spare_matrix(string say) {
    string name;
    while(1) {
        system("clear");
        cout<<"Matrix list:"<<endl;
        for(int i = 0; i < numbers_of_spare_martix; i++) {
            cout<<"    "<<all_spare_matrix[i].name()<<endl;
        }
        cout<<endl<<"Please input matrix name for "<<say<<endl<<"(enter \"0\" will stop this operation): ";
        cin>>name;
        if(name == "0") break;;
        for(int i = 0; i < numbers_of_spare_martix; i++) {
            if(all_spare_matrix[i].name() == name) {
                system("clear");
                cout<<name<<":"<<endl;
                return all_spare_matrix[i];
            }
        }
        cout<<"Can't find correspond matrix name.";
    }
    return spare_matrix();
}

bool check_same_name(string name) {
    for(int i = 0; i < numbers_of_spare_martix; i++) {
        if(all_spare_matrix[i].name() == name) {
            cout<<"This name has been use."<<endl;
            wait();
            system("clear");
            return true;
        }
    }
    return false;
}

void save_matrix(spare_matrix matrix) {
    string name;
    while(1) {
        cout<<"If you want to save this matrix, input 'Y' to save, or input 'N' to leave: ";
        cin.ignore();
        char c = getchar();
        if(c == 'Y') {
            system("clear");
            while(1) {
                show_matrix(matrix);
                cout<<"Please enter matrix's name: ";
                cin>>name;
                if(check_same_name(name)) continue;
                break;
            }
            matrix.set_name(name);
            all_spare_matrix[numbers_of_spare_martix] = spare_matrix(matrix);
            numbers_of_spare_martix++;
            show_matrix(matrix);
            cout<<"Matrix "<<name<<" has been saved."<<endl;
        }
        if(c == 'N') {
            break;
        }
    }
}

int main() {
    while(1) {
        int64_t choose;
        hello();        
        cin>>choose;
        system("clear");
        if(choose == 1) {
            string name;
            int64_t row, col, num;
            bool input_hash[101][101] = {{false}};
            spare_matrix &cur_matrix = all_spare_matrix[numbers_of_spare_martix];
            while(1) {
                cout<<"Please input martix name: ";
                cin>>name;
                if(check_same_name(name)) continue;
                cur_matrix.set_name(name);
                break;
            }
            while(1) {
                cout<<"Please input martix row(1-100): ";
                cin>>row;
                if(cur_matrix.set_row(row) == 0) {
                    cout<<"You only allow set row within 1-100."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                break;
            }
            while(1) {
                cout<<"Please input martix column(1-100): ";
                cin>>col;
                if(cur_matrix.set_col(col) == 0) {
                    cout<<"You only allow set column within 1-100."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                break;
            }
            while(1) {
                show_matrix(cur_matrix);
                cout<<"Please input data row(1-"<<cur_matrix.row()<<")(input 0 to stop): ";
                cin>>row;
                if(row == 0) break;
                cout<<"Please input data column(1-"<<cur_matrix.col()<<")(input 0 to stop): ";
                cin>>col;
                if(row == 0) break;
                cout<<"Please input data: ";
                cin>>num;
                if(input_hash[row][col]) {
                    cout<<"You have been input this element."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                if(cur_matrix.set_data(row, col, num) == 0) {
                    cout<<"Please input row and column in range."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                input_hash[row][col] = true;
            }
            cur_matrix.sort_data();
            show_matrix(cur_matrix);
            numbers_of_spare_martix++;
        }
        else if(choose == 2) {
            if(matrix_amount_less(1) == false) continue;
            spare_matrix cur_matrix = find_spare_matrix("display");
            if(cur_matrix.size() == 0) continue;
            show_matrix(cur_matrix);
        }
        else if(choose == 3) {
            if(matrix_amount_less(1) == false) continue;
            spare_matrix cur_matrix = find_spare_matrix("submatrix");
            if(cur_matrix.size() == 0) continue;
            int64_t row, col, rows[MAX_ROW + 1] = {0}, cols[MAX_COL + 1] = {0}, row_size = 0, col_size = 0;
            bool row_hash[MAX_ROW + 1] = {false}, col_hash[MAX_COL + 1] = {false};
            while(1) {
                show_matrix(cur_matrix);
                cout<<"Select row: ";
                for(int i = 0; i < row_size; i++) {
                    cout<<rows[i]<<" ";
                }
                cout<<endl;
                cout<<"Select col: ";
                for(int i = 0; i < col_size; i++) {
                    cout<<cols[i]<<" ";
                }
                cout<<endl;
                cout<<"Please input the row(1-"<<cur_matrix.row()<<") submatrix you want(input 0 to stop):";
                cin>>row;
                if(row == 0) break;
                if(row < 0 || cur_matrix.row() < row) {
                    cout<<"Please input row in range."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                if(row_hash[row]) {
                    cout<<"You have been input this row."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                rows[row_size++] = row;
                row_hash[row] = true;
            }
            while(1) {
                show_matrix(cur_matrix);
                cout<<"Select row: ";
                for(int i = 0; i < row_size; i++) {
                    cout<<rows[i]<<" ";
                }
                cout<<endl;
                cout<<"Select col: ";
                for(int i = 0; i < col_size; i++) {
                    cout<<cols[i]<<" ";
                }
                cout<<endl;
                cout<<"Please input the column(1-"<<cur_matrix.col()<<") submatrix you want(input 0 to stop):";
                cin>>col;
                if(col == 0) break;
                if(col <= 0 || cur_matrix.col() < col) {
                    cout<<"Please input column in range."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                if(col_hash[col]) {
                    cout<<"You have been input this column."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                cols[col_size++] = col;
                col_hash[col] = true;
            }
            spare_matrix ans_matrix(cur_matrix.sub_matrix(rows, cols, row_size, col_size));
            show_matrix(ans_matrix);
            save_matrix(ans_matrix);
        }
        else if(choose == 4) {
            if(matrix_amount_less(1) == false) continue;
            spare_matrix cur_matrix = find_spare_matrix("transpose matrix");
            if(cur_matrix.size() == 0) continue;
            spare_matrix ans_matrix(cur_matrix.transpose());
            show_matrix(ans_matrix);
            save_matrix(ans_matrix);
        }
        else if(choose == 5) {
            if(matrix_amount_less(1) == false) continue;
            spare_matrix ans_matrix;
            while(1) {
                spare_matrix first_matrix = find_spare_matrix("first product matrix");
                if(first_matrix.size() == 0) break;
                spare_matrix second_matrix = find_spare_matrix("second product matrix");
                if(second_matrix.size() == 0) break;
                ans_matrix = first_matrix.element_wise_product(second_matrix);
                if(ans_matrix.size() == 0) {
                    cout<<"You need to choose two matrixs with same row and column."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                break;
            }
            if(ans_matrix.size() == 0) continue;
            show_matrix(ans_matrix);
            save_matrix(ans_matrix);
        }
        else if(choose == 6) {
            if(matrix_amount_less(1) == false) continue;
            spare_matrix ans_matrix;
            while(1) {
                spare_matrix first_matrix = find_spare_matrix("first multiplication matrix");
                if(first_matrix.size() == 0) break;
                spare_matrix second_matrix = find_spare_matrix("second multiplication matrix");
                if(second_matrix.size() == 0) break;
                ans_matrix = first_matrix.multiplication(second_matrix);
                if(ans_matrix.size() == 0) {
                    cout<<"You need to choose two matrixs with first matrix column euqal to second matrix row."<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                break;
            }
            if(ans_matrix.size() == 0) continue;
            show_matrix(ans_matrix);
            save_matrix(ans_matrix);
        }
        else if(choose == 7) {
            if(matrix_amount_less(1) == false) continue;
            spare_matrix ans_matrix;
            while(1) {
                spare_matrix cur_matrix = find_spare_matrix("square_multiplication");
                if(cur_matrix.size() == 0) break;
                int64_t times = 1;
                while(1) {
                    show_matrix(cur_matrix);
                    cout<<"Please input power(2-): ";
                    cin>>times;
                    if(times < 2) {
                        cout<<"Your power need large 2."<<endl;
                        wait();
                        system("clear");
                        continue;
                    }
                    break;
                }
                ans_matrix = cur_matrix.square_multiplication(times);
                if(ans_matrix.size() == 0) {
                    cout<<"Selected matrix is not square matrix"<<endl;
                    wait();
                    system("clear");
                    continue;
                }
                ans_matrix.set_name(cur_matrix.name() + "^" + to_string(times));
                break;
            }
            if(ans_matrix.size() == 0) continue;
            show_matrix(ans_matrix);
            save_matrix(ans_matrix);
        }
        else if(choose == 8) {
            cout<<"EXIT."<<endl;
            exit(0);
        }
        else {
            cout<<"EXIT."<<endl;
            exit(0);
        }
        wait();
    }
}