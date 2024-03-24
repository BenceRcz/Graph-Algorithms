#pragma once

#include <vector>

#define ui unsigned int

using namespace std;

// This function implements the Depth first search algorithm in an iterative manner
void dfs_itr(const vector<vector<ui>>& adj_list, const ui& n, const ui& source_node);

// This function implements the Breadth first search algorithm in an iterative manner
void bfs_itr(const vector<vector<ui>>& adj_list, const ui& n, const ui& source_node);