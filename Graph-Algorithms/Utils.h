#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

#define ui unsigned int

class link {
private:
	ui from;
	ui to;
	short weight;

public:
	link() = default;
	link(ui from, ui to, short value);
	friend std::ostream& operator << (std::ostream& os, const link& obj);
};


// This function creates a short matrix of size row * col
short** create_matrix(const ui& row, const ui& col);

// This function deletes a matrix with a row count of row
void delete_matrix(short** a, const ui& row);

// This function reads the input from file named path
// Returns adjacency matrix
short** read_weighted_matrix(string path, ui& n, ui& m);

// This function reads an undirected weighted edje list from a given file
// Returns weighted edje list
vector<link> read_weighted_edje_list(string path, ui& n, ui& m);

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

// This function reads a directed unweighted graph from a file named path
// Returns unweighted adjacency list
vector<vector<ui>> read_unweighted_directed_list(string path, ui& n, ui& m);

// This function searches for a cycle inside a directed graph
// Returns boolean value
bool directedContainsCycle(const vector<vector<ui>>& adj_list, const ui& n);

// This function returns the K. neighbour of a node
vector<ui> kNeighbour(const vector<vector<ui>>& adj_list, const ui& n, const ui& node, const ui& k);

// This function sorts the given Graph in a topological order
// Returns a stack containing the order
stack<ui> TopoSort(const vector<vector<ui>>& adj_list, const ui& n);
