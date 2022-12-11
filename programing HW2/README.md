# Data Sutructure Programing HW2

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
`g++ -o polynomial_calculate polynomial_calculate_lib.cpp polynomial_calculate.cpp` to compile all file, the excutable excutable file is "polynomial_calculate".

Please follow the instruction in terminal, I only support wrong input with number. If the program ask you to input nubmer, please input the number, or the program operations would be undefined, and you need to stop the program and restart it. And, this matrix only support integer.

This program support store max 100 matrixs.

My all of sparse matrix operations were packaged in class `polynomial`(in `polynomial.h`).
And UI function(such as show_data) is in `polynomial_calculate_lib.cpp`.

<div style="page-break-after: always;"></div>

## Introduction

There's 10 operations:

>

1. Add new polynomial
2. Display polynomial
3. Display indicate term's coefficient
4. Add new term
5. Remove the term
6. Add two polynomial
7. Subtract two polynomial
8. Multiply two polynomial
9. divided two polynomial
10. EXIT

### 1. Add new polynomial

You can init a polnomial with a name and input the coefficient and power term by term.

### 2. Display polynomial

Choose the polnomial you want to display.

### 3. Display indicate term's coefficient

You need to choose the polnomial first, then input the power which is the term you want to show.

### 4. Add new term

You need to choose the polnomial first, then input the power and coefficient you wnat to add.

### 5. Remove the term

You need to choose the polnomial first, then input the power and coefficient you wnat to remove.

### 6. Add two polynomial

You nee to choose two polnomials A and B, and it can be same.
Then, porgrma will show A + B.

### 7. Subtract two polynomial

You nee to choose two polnomials A and B, and it can be same.
Then, porgrma will show A - B.

### 8. Multiply two polynomial

You nee to choose two polnomials A and B, and it can be same.
Then, porgrma will show A \* B.

### 9. divided two polynomial

You nee to choose two polnomials A and B, and it can be same.
Then, porgrma will show A / B.

### 10. EXIT

Program will stop.

## Time Compelxity Analyze

### 1. Add new polynomial

We suppose we have n term to input.  
For each insert new term, the program will search each term and insert in
appropriate position. So it's Time complexity is O(n^2).

### 2. Display polynomial

We suppose polynomial has n terms.  
The program will show all term, so it's time compelxity is O(n).

### 3. Display indicate term's coefficient

We suppose polynomial has n terms.  
Then the program will search each term, so it's time compelxity is O(n).

### 4. Add new term

We suppose polynomial has n terms.  
Then the program will search each term, and insert in
appropriate position. So, it's time compelxity is O(n).

### 5. Remove the term

We suppose polynomial has n terms.  
Then the program will search each term, and remove it. So, it's time compelxity is O(n).

### 6. Add two polynomial

We suppose polynomial1 has n terms, suppose polynomial2 has m terms.  
The program will use two pointers to compare each term. So the time complexity is O(n + m).

### 7. Subtract two polynomial

We suppose polynomial1 has n terms, suppose polynomial2 has m terms.  
The program will use two pointers to compare each term. So the time complexity is O(n + m).

### 8. Multiply two polynomial

We suppose polynomial1 has n terms, suppose polynomial2 has m terms.  
The program will multiply each term of two polynomials, and insert it to a new polynomial, the new polynomial will n + m terms at most. So, the time complexity is O(n \* m \* (n + m))

### 9. divided two polynomial

We suppose polynomial1 has n terms, suppose polynomial2 has m terms.  
The program will divide from polynomial1 highest term power to polynomial2 highest term power, it need excute n - m times at most. Then, it need to minus polynomial1 after divide, it need O(m). So, the time complexity is O((n - m) \* m).
