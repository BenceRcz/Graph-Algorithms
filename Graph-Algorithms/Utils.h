#pragma once

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define ui unsigned int

// This function creates a short matrix of size row * col
short** create_matrix(const ui& row, const ui& col);

// This function deletes a matrix with a row count of row
void delete_matrix(short** a, const ui& row);
// This function reads the input from file named path
// Returns adjacency matrix
short** read_weighted_matrix(string path, ui& n, ui& m);
// This function reads the input from a file named path
// Returns unweighted adjacency list
vector<vector<ui>> read_unweighted_list(string path, ui& n, ui& m);

// This function prints a vector
template <typename T>
void print_vector(const vector<T>& vec);

// This function prints a matrix of size n * m
void print_matrix(short** a, const ui& row, const ui& col);


// This function prints an adjacency list
void print_adj_list(const vector<vector<pair<ui, short>>>& adj_list, const ui& n);
