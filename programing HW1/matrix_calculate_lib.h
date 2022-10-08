#pragma once

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "sparse_matrix.h"
using namespace std;

void print_line();
void wait();
void hello();
bool matrix_amount_less(int64_t num);
void show_matrix(sparse_matrix matrix);
sparse_matrix find_sparse_matrix(string say);
bool check_same_name(string name);
void save_matrix(sparse_matrix matrix);
