# Data Sutructure Programing HW1
## 41047025S 王重鈞

### README

lang: cpp14  
environment: linux or mac  

Use 
`make` 
or 
`g++ -o matrix_calculate matrix_calculate_lib.cpp matrix_calculate.cpp` to compile all file, the excutable file name is "matrix_calculate".

Please follow the instruction in terminal, I only support wrong input with number. If the program ask you to input nubmer, please input the number, or the program operations would be undefined, and you need to stop the program and restart it.

This program support stort max 10 matrix if your memory enough.

This sparse matrix support 50\*50 matrix with 1000 element. However, I recommand use your matrix `m + n` less than 50.

My all of sparse matrix operations were packaged in class `sparse matrix`(in `sparse_matrix.h`).
And UI function(such as show_data) is in `matrix_calculate_lib.cpp`.

### Time complexity

Following I will only analyze time complexity with sparse operation beause it's the most impartant part this class.

Besdies, for showing matrix, it's time complexity O(row * col). It's UI part, but there's many asking me to "display". However, I think it's should be anslyze in sparse matrix time complexity, so I previously analyze it here.


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
`multiplication()`: O((M1_cols * M2_terms) + (M2_col * M1_terms))  
`set_data()`: O(1)  

Total: O((M1_cols * M2_terms) + (M2_col * M1_terms))

#### 讀入一個square matrix M，計算M^k(k為大於等於2的整數)，以最少的matrix相乘次數計算出M^k並顯示M^k的結果

sparse opeation:  
`square_multiplication`: O(log(power) * O(multiplication))  
 = O(log(power) + (M_cols * M_terms) + (M_col * M_terms))  
 = O(log(power) + M_cols * M_terms)  
 
Total: O(log(power) + M_cols * M_terms)
