#include <stack>
#include <queue>
#include "Utils.h"

using namespace std;

#define PRINT_PATH true

// This function implements the Depth first search algorithm in an iterative manner
void dfs_itr(const vector<vector<ui>>& adj_list, const ui& n, const ui& source_node) {
	bool* visited = new bool[n] {0};
	ui cur_node;
	stack<ui> stack;
	stack.push(source_node);

	while (!stack.empty()) {
		cur_node = stack.top();
		stack.pop();

		if (!visited[cur_node - 1]) {
			visited[cur_node - 1] = true;
			if (PRINT_PATH) {
				cout << cur_node << " ";
			}
		}

		for (ui i = 0; i < adj_list[cur_node - 1].size(); ++i) {
			if (!visited[adj_list[cur_node - 1][i] - 1]) {
				stack.push(adj_list[cur_node - 1][i]);
			}
		}
	}

	delete[] visited;
}

// This function implements the Breadth first search algorithm in an iterative manner
void bfs_itr(const vector<vector<ui>>& adj_list, const ui& n, const ui& source_node) {
	bool* visited = new bool[n] {0};
	ui cur_node;
	queue<ui> queue;
	queue.push(source_node);

	while (!queue.empty()) {
		cur_node = queue.front();
		queue.pop();

		if (!visited[cur_node - 1]) {
			visited[cur_node - 1] = true;
			if (PRINT_PATH) {
				cout << cur_node << " ";
			}
		}

		for (ui i = 0; i < adj_list[cur_node - 1].size(); ++i) {
			if (!visited[adj_list[cur_node - 1][i] - 1]) {
				queue.push(adj_list[cur_node - 1][i]);
			}
		}
	}

	delete[] visited;
}

int main() {
	ui n, m;
	vector<vector<ui>> adj_list = read_unweighted_list("unweighted_graph1.in", n, m);
	bfs_itr(adj_list, n, 1);
	return 0;
}