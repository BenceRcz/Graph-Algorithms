#include "Utils.h"

using namespace std;

class link {
private:
	ui from;
	ui to;
	short weight;

public:
	link(ui from, ui to, short value) {
		this->from = from;
		this->to = to;
		this->weight = value;
	}

	friend std::ostream& operator << (std::ostream& os, const link& obj) {
		os << obj.from + 1 << " -> " << obj.to << ": " << obj.weight;
		return os;
	}
};

// This function creates and returns an incidence matrix out of a given adj_matrix
short** create_inc_matrix(short** adj_matrix, const ui& n, const ui& m) {
	short** inc_matrix = create_matrix(n, m);
	ui curr = 0;

	for (ui i = 0; i < n; ++i) {
		for (ui j = i; j < n; ++j) {
			if (adj_matrix[i][j] != 0) {
				inc_matrix[i][curr] = adj_matrix[i][j];
				inc_matrix[j][curr] = adj_matrix[i][j];
				++curr;
			}
		}
	}

	return inc_matrix;
}

// This function creates an adjacency list from an incidence matrix
vector<vector<pair<ui, short>>> create_adj_list(short** inc_matrix, const ui& n, const ui& m) {
	vector<vector<pair<ui, short>>> list;
	ui node = 0, cur_node = 0;
	short weight;
	list.resize(n);

	for (ui j = 0; j < m; ++j) {
		node = UINT_MAX;
		cur_node = UINT_MAX;
		for (ui i = 0; i < n; ++i) {
			if (inc_matrix[i][j] != 0) {
				if (node == UINT_MAX) {
					weight = inc_matrix[i][j];
					node = i;
				}
				else {
					cur_node = i;
					list[node].push_back(std::make_pair(i + 1, weight));
					list[i].push_back(std::make_pair(node + 1, weight));
				}
			}
		}
		if (cur_node == UINT_MAX && node != UINT_MAX) {
			list[node].push_back(std::make_pair(node + 1, weight));
		}
	}

	return list;
}

// This function creates an edge list out of an adjacency list
vector<link> create_edge_list(const vector<vector<pair<ui, short>>>& adj_list, const ui& n) {
	vector<link> links;
	for (ui i = 0; i < n; ++i) {
		for (ui j = 0; j < adj_list[i].size(); ++j) {
			links.push_back(link(i, adj_list[i][j].first, adj_list[i][j].second));
		}
	}
	return links;
}

// This function retreives the isolated nodes from the adjacency matrix
vector<ui> get_isolated_nodes(short** adj_matrix, const ui& n) {
	vector<ui> isolated_nodes;
	bool is_isolated = true;
	for (ui i = 0; i < n; ++i) {
		is_isolated = true;
		for (ui j = 0; j < n; ++j) {
			if (adj_matrix[i][j] != 0) {
				is_isolated = false;
			}
		}
		if (is_isolated) {
			isolated_nodes.push_back(i + 1);
		}
	}
	return isolated_nodes;
}

// This function gets the endpoints from an incidence matrix
vector<ui> get_endpoints(short** inc_matrix, const ui& n, const ui& m) {
	vector<ui> endpoints;
	ui links = 0;

	for (ui i = 0; i < n; ++i) {
		links = 0;
		for (ui j = 0; j < m; ++j) {
			if (inc_matrix[i][j] != 0) {
				++links;
			}
		}
		if (links == 1) {
			endpoints.push_back(i + 1);
		}
	}
	return endpoints;
}

// This function returns is the matrix is regular using an adjacency matrix
bool is_regular(const ui& n, short** adj_matrix) {
	ui fst_reg = 0, cur_reg = 0;
	for (ui j = 0; j < n; ++j) {
		if (adj_matrix[0][j] != 0) {
			++fst_reg;
		}
	}

	for (ui i = 1; i < n; ++i) {
		cur_reg = 0;
		for (ui j = 0; j < n; ++j) {
			if (adj_matrix[i][j] != 0) {
				++cur_reg;
			}
		}
		if (cur_reg != fst_reg) {
			return false;
		}
	}

	return true;
}

//int main() {
//	ui n, m;
//	short** adj_matrix = read_weighted_matrix("graph2.in", n, m);
//	cout << "----------------ADJACENCY MATRIX----------------" << endl;
//	print_matrix(adj_matrix, n, n);
//	short** inc_matrix = create_inc_matrix(adj_matrix, n, m);
//	cout << "----------------INCIDENCE MATRIX----------------" << endl;
//	print_matrix(inc_matrix, n, m);
//	vector<vector<pair<ui, short>>> adj_list = create_adj_list(inc_matrix, n, m);
//	cout << "-----------------ADJACENCY LIST-----------------" << endl;
//	print_adj_list(adj_list, n);
//	vector<link> links = create_edge_list(adj_list, n);
//	cout << "--------------------EDGE LIST-------------------" << endl;
//	print_vector(links);
//	vector<ui> isolated_nodes = get_isolated_nodes(adj_matrix, n);
//	cout << "-----------------ISOLATED NODES-----------------" << endl;
//	print_vector(isolated_nodes);
//	vector<ui> endpoints = get_endpoints(inc_matrix, n, m);
//	cout << "--------------------ENDPOINTS-------------------" << endl;
//	print_vector(endpoints);
//	cout << endl;
//	if (is_regular(n, adj_matrix)) {
//		cout << "The graph is regular" << endl;
//	}
//	else {
//		cout << "The graph isn't regular" << endl;
//	}
//
//	delete_matrix(adj_matrix, n);
//	delete_matrix(inc_matrix, n);
//
//	return 0;
//}