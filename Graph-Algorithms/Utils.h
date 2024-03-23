#pragma once

#define ui unsigned int

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
vector<vector<ui>> read_unweighted_list(string path, ui&n, ui& m) {
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
