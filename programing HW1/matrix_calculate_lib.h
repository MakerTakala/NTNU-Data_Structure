#pragma once

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string.h>
#include "sparse_matrix.h"
using namespace std;

void print_line();
void wait();
void hello();
bool matrix_amount_less(int64_t num);
void show_matrix(sparse_matrix matrix);
sparse_matrix find_sparse_matrix(const char say[]);
bool check_same_name(char name[]);
void save_matrix(sparse_matrix &matrix);
