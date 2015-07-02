#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include<iomanip>
#include<string>
#include<cstring>
#include<map>
const int inf = 1000 * 1000 * 1000;

bool path_avail(std::vector<std::vector<int>> &graph, int s, int f, std::vector<int> &path) {
	path.clear();
	std::vector<bool> used(graph.size(), 0);
	std::vector<int> parent(graph.size(), -1);
	std::queue<int> queue;
	queue.push(s);
	int fl = 0;
	used[s] = 1;
	while (!queue.empty()) {
		int elem = queue.front();
		queue.pop();
		for (int i = 0; i < graph[elem].size(); ++i) {
			if (graph[elem][i] != 0 && !used[i]) {
				queue.push(i);
				used[i] = 1;
				parent[i] = elem;
				if (i == f) {
					fl = 1;
					break;
				}
			}
		}
		if (fl) {
			break;
		}
	}
	if (!fl) {
		return false;
	}
	else {
		int vertex = f;
		path.push_back(f);
		while (vertex != s) {
			path.push_back(parent[vertex]);
			vertex = parent[vertex];
		}
		std::reverse(path.begin(), path.end());
		return true;
	}

}
int edmons_karp(std::vector<std::vector<int>> graph, std::vector<std::vector<int>> residual_network, int s, int f) {
	std::vector<int> path;
	while (path_avail(graph, s, f, path)) {
		int c_min = inf;
		for (int i = 0; i < path.size() - 1; ++i) {
			int from = path[i];
			int to = path[i + 1];
			if (graph[from][to] < c_min) {
				c_min = graph[from][to];
			}
		}
		for (int i = 0; i < path.size() - 1; ++i) {
			int from = path[i];
			int to = path[i + 1];
			graph[from][to] -= c_min;
			residual_network[from][to] += c_min;
			graph[to][from] = residual_network[from][to];


		}
	}
	int flow = 0;
	for (int i = 0; i < residual_network.size() - 1; ++i) {
		flow += residual_network[i][f];
	}
	return flow;
}


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> residual_network(n + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
        int a, b, cc;
        std::cin >> a >> b >> cc;
        --a; --b;
        graph[a][b] = cc;
    }
    std::cout<<edmons_karp(graph, residual_network, 0, n - 1);
   
    int y;
    std::cin >> y;
}

