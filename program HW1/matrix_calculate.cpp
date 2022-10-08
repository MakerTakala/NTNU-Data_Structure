#include "matrix_calculate_lib.h"
#include "sparse_matrix.h"

sparse_matrix all_sparse_matrix[105];
int64_t numbers_of_sparse_martix = 0;

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
            if(numbers_of_sparse_martix > 99) {
                cout<<"This program only support 100 matrixs."<<endl;
                wait();
            }
            sparse_matrix &cur_matrix = all_sparse_matrix[numbers_of_sparse_martix];
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
            numbers_of_sparse_martix++;
        }
        else if(choose == 2) {
            if(matrix_amount_less(1) == false) continue;
            sparse_matrix cur_matrix = find_sparse_matrix("display");
            if(cur_matrix.size() == 0) continue;
            show_matrix(cur_matrix);
        }
        else if(choose == 3) {
            if(matrix_amount_less(1) == false) continue;
            sparse_matrix cur_matrix = find_sparse_matrix("submatrix");
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
            sparse_matrix ans_matrix(cur_matrix.sub_matrix(rows, cols, row_size, col_size));
            if(ans_matrix.size() == 0) continue;
            show_matrix(ans_matrix);
            if(numbers_of_sparse_martix <= 99) save_matrix(ans_matrix);
        }
        else if(choose == 4) {
            if(matrix_amount_less(1) == false) continue;
            sparse_matrix cur_matrix = find_sparse_matrix("transpose matrix");
            if(cur_matrix.size() == 0) continue;
            sparse_matrix ans_matrix(cur_matrix.transpose());
            show_matrix(ans_matrix);
            if(numbers_of_sparse_martix <= 99) save_matrix(ans_matrix);
        }
        else if(choose == 5) {
            if(matrix_amount_less(1) == false) continue;
            sparse_matrix ans_matrix;
            while(1) {
                sparse_matrix first_matrix = find_sparse_matrix("first product matrix");
                if(first_matrix.size() == 0) break;
                sparse_matrix second_matrix = find_sparse_matrix("second product matrix");
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
            if(numbers_of_sparse_martix <= 99) save_matrix(ans_matrix);
        }
        else if(choose == 6) {
            if(matrix_amount_less(1) == false) continue;
            sparse_matrix ans_matrix;
            while(1) {
                sparse_matrix first_matrix = find_sparse_matrix("first multiplication matrix");
                if(first_matrix.size() == 0) break;
                sparse_matrix second_matrix = find_sparse_matrix("second multiplication matrix");
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
            if(numbers_of_sparse_martix <= 99) save_matrix(ans_matrix);
        }
        else if(choose == 7) {
            if(matrix_amount_less(1) == false) continue;
            sparse_matrix ans_matrix;
            while(1) {
                sparse_matrix cur_matrix = find_sparse_matrix("square_multiplication");
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
            if(numbers_of_sparse_martix <= 99) save_matrix(ans_matrix);
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
    wait();
}