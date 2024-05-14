#include "Utils.h"

// This function implements kruskals algorithm to find an mst
// returns the mst of a given graph
void mst_kruskal(const vector<link>& edge_list, const ui& n) {
	DisjointSets disjSet(n);
}

int main() {
	ui n, m;
	vector<link> edge_list = read_weighted_edge_list("weighted_graph1.in", n, m);
	cout << "1";
	return 0;
}