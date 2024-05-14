#include "Utils.h"

link::link(ui from, ui to, short value) {
	this->from = from;
	this->to = to;
	this->weight = value;
}

std::ostream& operator << (std::ostream& os, const link& obj) {
	os << obj.from + 1 << " -> " << obj.to << ": " << obj.weight;
	return os;
}

// This function creates a short matrix of size row * col
short** create_matrix(const ui& row, const ui& col) {
	short** a = new short* [row] {};
	for (ui i = 0; i < row; ++i) {
		a[i] = new short[col] {0};
	}
	return a;
}

// This function deletes a matrix with a row count of row
void delete_matrix(short** a, const ui& row) {
	for (ui i = 0; i < row; ++i) {
		delete[] a[i];
	}
	delete[] a;
}

// This function reads the input from file named path
// Returns adjacency matrix
short** read_weighted_matrix(string path, ui& n, ui& m) {
	ui from, to;
	short weight;
	ifstream f(path);
	f >> n >> m;
	short** adj_matrix = create_matrix(n, n);

	for (ui i = 0; i < m; ++i) {
		f >> from >> to >> weight;
		adj_matrix[from - 1][to - 1] = weight;
		adj_matrix[to - 1][from - 1] = weight;
	}

	return adj_matrix;
}

// This function reads the input from a file named path
// Returns unweighted adjacency list
vector<vector<ui>> read_unweighted_list(string path, ui& n, ui& m) {
	vector<vector<ui>> adj_list;
	ui from, to;
	ifstream f(path);
	f >> n >> m;
	adj_list.resize(n);

	for (ui i = 0; i < m; ++i) {
		f >> from >> to;
		adj_list[from - 1].push_back(to);
		adj_list[to - 1].push_back(from);
	}

	return adj_list;
}

// This function reads a directed unweighted graph from a file named path
// Returns unweighted adjacency list
vector<vector<ui>> read_unweighted_directed_list(string path, ui& n, ui& m) {
	vector<vector<ui>> adj_list;
	ui from, to;
	ifstream f(path);
	f >> n >> m;
	adj_list.resize(n);

	for (ui i = 0; i < m; ++i) {
		f >> from >> to;
		adj_list[from - 1].push_back(to);
	}

	return adj_list;
}

// This function reads an undirected weighted edje list from a given file
// Returns weighted edje list
vector<link> read_weighted_edge_list(string path, ui& n, ui& m) {
	vector<link> edj_list;
	ui from, to;
	short weight;
	ifstream f(path);
	f >> n >> m;

	for (ui i = 0; i < m; ++i) {
		f >> from >> to >> weight;
		edj_list.push_back(link(from, to, weight));
	}

	return edj_list;
}

// This function prints a vector
template <typename T>
void print_vector(const vector<T>& vec) {
	for (ui i = 0; i < vec.size(); ++i) {
		cout << vec[i] << endl;
	}
}

// This function prints a matrix of size n * m
void print_matrix(short** a, const ui& row, const ui& col) {
	for (ui i = 0; i < row; ++i) {
		for (ui j = 0; j < col; ++j) {
			cout << "   " << a[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

// This function prints an adjacency list
void print_adj_list(const vector<vector<pair<ui, short>>>& adj_list, const ui& n) {
	for (ui i = 0; i < n; ++i) {
		cout << i + 1 << ": ";
		for (ui j = 0; j < adj_list[i].size(); ++j) {
			cout << "-> " << adj_list[i][j].first << ": " << adj_list[i][j].second << " ";
		}
		cout << endl;
	}
}

// This function declares a compare function for 2 link objects
// Returns if a is smaller then b
bool compare(link a, link b) {
	return a.weight < b.weight;
}

// This function searches for a cycle inside a directed graph
// Returns boolean value
bool directedContainsCycle(const vector<vector<ui>>& adj_list, const ui& n) {
	short* visited = new short[n] {0};			// 0 - not visited, 1 - visited, but will return, 2 - won't return
	ui cur_node = 0;
	stack<ui> stack;
	stack.push(1);

	while (!stack.empty()) {
		cur_node = stack.top();
		
		if (visited[cur_node - 1] == 0) {
			visited[cur_node - 1] = 1;

			for (ui i = 0; i < adj_list[cur_node - 1].size(); ++i) {
				if (visited[adj_list[cur_node - 1][i] - 1] == 0) {
					stack.push(adj_list[cur_node - 1][i]);
				}
				else {
					if (visited[adj_list[cur_node - 1][i] - 1] == 1) {
						return true;
					}
				}
			}
		}
		else {
			stack.pop();
			if (visited[cur_node - 1] == 1) {
				visited[cur_node - 1] = 2;
			}
		}
	}

	delete[] visited;
	return false;
}

// This function returns the K. neighbour of a node
vector<ui> kNeighbour(const vector<vector<ui>>& adj_list, const ui& n, const ui& node, const ui& k) {
	vector<ui> neighbours;
	queue<ui> queue;
	ui cur_node, cur_dist = 1;
	ui* dist = new ui[n]{ 0 };
	bool* visited = new bool[n] {0};
	queue.push(node);

	while (!queue.empty()) {
		cur_node = queue.front();
		queue.pop();
		
		if (!visited[cur_node - 1]) {
			visited[cur_node - 1] = true;
			if (dist[cur_node - 1] == k) {
				neighbours.push_back(cur_node);
			}
		}

		for (ui i = 0; i < adj_list[cur_node - 1].size(); ++i) {
			if (!visited[ adj_list[cur_node - 1][i] - 1 ]) {
				queue.push(adj_list[cur_node - 1][i]);

				if (dist[ adj_list[cur_node - 1][i] - 1 ] == 0 && adj_list[ cur_node - 1 ][i] != node) {
					dist[ adj_list[cur_node - 1][i] - 1 ] = cur_dist;
				}
			}
		}

		++cur_dist;
	}
	 
	delete[] visited;
	delete[] dist;

	return neighbours;
}

// This function sorts the given Graph in a topological order
// Returns a stack containing the order
stack<ui> TopoSort(const vector<vector<ui>>& adj_list, const ui& n) {
	ui* visits = new ui[n] {0};
	ui cur_node;
	stack<ui> stack, order;
	stack.push(1);

	while (!stack.empty()) {
		cur_node = stack.top();

		if (visits[cur_node - 1] == 0) {
			++visits[cur_node - 1];

			for (ui i = 0; i < adj_list[cur_node - 1].size(); ++i) {
				if (visits[adj_list[cur_node - 1][i] - 1] == 0) {
					stack.push(adj_list[cur_node - 1][i]);
				}
			}
		}
		else {
			if (visits[cur_node - 1] == 1) {
				++visits[cur_node - 1];
				order.push(cur_node);
			}

			stack.pop();
		}
	}

	delete[] visits;
	return order;
}

//
//int main() {
//	ui n, m;
//	vector<vector<ui>> adj_list = read_unweighted_directed_list("unweighted_graph1.in", n, m);
//	stack<ui> topo = TopoSort(adj_list, n);
//	return 0;
//}