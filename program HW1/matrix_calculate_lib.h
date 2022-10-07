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
void show_matrix(spare_matrix matrix);
spare_matrix find_spare_matrix(string say);
bool check_same_name(string name);
void save_matrix(spare_matrix matrix);

spare_matrix all_spare_matrix[100];
int64_t numbers_of_spare_martix = 0;