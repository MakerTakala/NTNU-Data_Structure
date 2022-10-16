## Time complexity analyze

### saprse matrix function

parivate:  

`void __set_name(string)`: O(1)

`void __set_row(int64_t)`: O(1)

`void __set_col(int64_t)`: O(1)

`void __set_data(int64_t, int64_t, int64_t)`: O(1)


public:  

`int64_t row()`: O(1)

`int64_t col()`: O(1)

`string name()`: O(1)

`int64_t size()`: O(1)

`sparse_matrix()`: O(MAX_TERMS)  
Construct a new matrix, it's need O(MAX_TERMS) to clean data.

`sparse_matrix(const sparse_matrix M)`: O(M_terms)  
Copy a matrix from M, it's need O(M_terms) to copy the data.

`sparse_matrix(const int64_t row, const int64_t col, const string name)`: O(MAX_ELEMENTS)  
Constrcut a new matrix with indicate row, colimn and name, and it need O(MAX_ELEMENTS) to clean data.

`int set_name(string name)`: O(1)  

`int set_row(int64_t row)`: O(1)  

`int set_col(int64_t col)`: O(1)  

`int set_data(int64_t row, int64_t col, int64_t data)`: O(1)  

`sparse_matrix sort_data()`: O(M_terms * log(M_terms))  
It will sort data, and the sort algorithm is O(M_terms * log(M_terms)).

`int64_t get_data(int64_t output[MAX_ROW][MAX_COL])`: O(M_terms)  
It will get all data in saprse matrix, and it's need O(M_terms).

`sparse_matrix sub_matrix(int64_t rows[], int64_t cols[], int64_t row_size, int64_t col_size)`: O(row_size * log(row_size) + col_size * log(col_size) + row_size * col_size)  
It will sort rows and cols first, and it need O(row_size * log(row_size) + col_size * log(col_size)).
Then, it will recreate a new sparse matrix to insert all indicate submatrix data, It need O(row_size * col_size).

`sparse_matrix transpose()`: O(M_cols + M_terms)  
There's two loop from 0 to M_cols and a loop from 0 to M_terms, so it's time complexity is O(M_cols + M_terms).

`sparse_matrix element_wise_product(sparse_matrix)`: O(M1_terms + M2_terms)  
There's two pointer will iterate all M1 terms and all M2 terms, so the time complexity is O(M1_terms + M2_terms).

`sparse_matrix multiplication(sparse_matrix)`: O((M1_cols * M2_terms) + (M2_rows * M1_terms))  
First, M2 will transpost once, it need O(M2_cols + M2_terms). Then, the row begining will iterate all M1 rows, and each time will iterate M2_cols * M1_row + M2_terms. It will equal to O(M1_cols * M2_terms) + (M2_rows * M1_terms).


`sparse_matrix square_multiplication(int64_t times)`: O(log(power) * M_cols * M_terms)  
Beacuse power will divide two, so it need O(log(times)). And each time it need to multiplie matrix, so total time complexity is 
O(log(power) * O(multiplication))  
= O(log(power) * ((M_cols * M_terms) + (M_col * M_terms)))  
= O(log(power) * M_cols * M_terms)  

### Program operation time complexity

#### 由鍵盤輸入一個matrix M

sparse opeation:  
`set_name()`: O(1)  
`set_row()`: O(1)  
`set_col()`: O(1)  
`set_data()`: O(1)  
`sort_data()`: O(M_terms * log(M_terms))   

Total: O(M_terms * log(M_terms))

#### 由螢幕顯示matrix M的內容

sparse opeation:  
`get_data()`: O(M_terms)  

Total: O(M_terms)

#### 指定matrix M之submatrix的行編號及列編號，顯示該submatrix的內容

sparse opeation:  
`sub_matrix()`: O(M_terms + select_row_size * select_col_size)  
`set_data()`: O(1)  

Total: O(M_terms + select_row_size * select_col_size)

<div style="page-break-after: always;"></div>

#### 顯示M的轉置矩陣內容
 
sparse opeation:  
 `transpose()`: O(M_cols + M_terms)  

Total: O(M_cols + M_terms)

#### 讀入兩個 matrix M1及M2，做M1及M2的元素相乘(element-wise product)，並顯示M1．M2的結果

sparse opeation:
`element_wise_product()`: O(M1_terms + M2_terms)  
`set_data()`: O(1)  

Total: O(M1_terms + M2_terms)

#### 讀入兩個matrix M1及M2，做M1及M2的矩陣相乘，並顯示M1*M2的結果

sparse opeation:  
`transpose()`: O(M2_cols + M2_terms)  
`multiplication()`: O((M1_cols * M2_terms) + (M2_rows * M1_terms))  
`set_data()`: O(1)  

Total: O((M1_cols * M2_terms) + (M2_rows * M1_terms))

#### 讀入一個square matrix M，計算M^k(k為大於等於2的整數)，以最少的matrix相乘次數計算出M^k並顯示M^k的結果

sparse opeation:  
`square_multiplication`: O(log(power) * M_cols * M_terms)  
 
Total: O(log(power) + M_cols * M_terms)
