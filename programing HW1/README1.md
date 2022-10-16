# Data Sutructure Programing HW1
#### 41047025S 王重鈞

## Index:
README:1  
Operation introduct: 2-10  
Time complexity analyze: 11-13  


## README

lang: cpp14  
environment: linux or mac  

Use 
`make` 
or 
`g++ -o matrix_calculate matrix_calculate_lib.cpp matrix_calculate.cpp` to compile all file, the excutable file name is "matrix_calculate".

Please follow the instruction in terminal, I only support wrong input with number. If the program ask you to input nubmer, please input the number, or the program operations would be undefined, and you need to stop the program and restart it.

This program support stort max 100 matrix.

This sparse matrix support 50\*50 matrix with 1000 element. However, I recommand use your matrix `row + column` less than 50.

My all of sparse matrix operations were packaged in class `sparse matrix`(in `sparse_matrix.h`).
And UI function(such as show_data) is in `matrix_calculate_lib.cpp`.
