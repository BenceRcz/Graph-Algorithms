#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

#define ui unsigned int

class link {
public:
    ui from;
    ui to;
    short weight;

	link() = default;
	link(ui from, ui to, short value);
	friend std::ostream& operator << (std::ostream& os, const link& obj);
};

struct DisjointSets {
    ui* parent, *rnk;
    ui size;

    DisjointSets() = default;

    DisjointSets(ui n) {
        this->size = n;
        parent = new ui[n + 1];
        rnk = new ui[n + 1];

        for (ui i = 0; i < n; ++i) {
            rnk[i] = 1;
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    ui find(ui u) {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    // Union by rank 
    void merge(ui x, ui y) {
        x = find(x), y = find(y);

        /* Make tree with smaller height
        a subtree of the other tree */
        if (rnk[x] > rnk[y]) {
            parent[y] = x;
        } else { // If rnk[x] <= rnk[y] 
            parent[x] = y;
        }

        if (rnk[x] == rnk[y]) {
            rnk[y]++;
        }
    }

    // Destructor
    ~DisjointSets() {
        delete[] parent;
        delete[] rnk;
    }
};

// This function declares a compare function for 2 link objects
// Returns if a is smaller then b
bool compare(link a, link b);

// This function creates a short matrix of size row * col
short** create_matrix(const ui& row, const ui& col);

// This function deletes a matrix with a row count of row
void delete_matrix(short** a, const ui& row);

// This function reads the input from file named path
// Returns adjacency matrix
short** read_weighted_matrix(string path, ui& n, ui& m);

// This function reads an undirected weighted edje list from a given file
// Returns weighted edje list
vector<link> read_weighted_edge_list(string path, ui& n, ui& m);

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
