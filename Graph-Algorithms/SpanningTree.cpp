#include "Utils.h"
#include <algorithm>

// This function implements kruskals algorithm to find an mst
// returns the mst of a given graph
vector<link> mst_kruskal(const vector<link>& edge_list, const ui& n, const ui& m) {
	vector<link> mst;
	DisjointSets disjSet(n);
	ui set_from, set_to;
	sort(edge_list.begin(), edge_list.end(), compare);

	for (ui i = 0; i < m; ++i) {
		set_from = disjSet.find(edge_list[i].from);
		set_to = disjSet.find(edge_list[i].to);

		if (set_from == set_to) {
			mst.push_back(link(edge_list[i].from, edge_list[i].to, edge_list[i].weight));
			disjSet.merge(set_from, set_to);
		}
	}

	return mst;
}

int main() {
	ui n, m;
	vector<link> edge_list = read_weighted_edge_list("weighted_graph1.in", n, m);
	cout << "1";
	return 0;
}