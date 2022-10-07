#pragma once

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

#define MAX_ROW 100
#define MAX_COL 100
#define MAX_ELEMENT 1000

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