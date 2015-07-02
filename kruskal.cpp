#include<vector>
#include<iostream>
#include<algorithm>
struct edge {
    int  from, to, weight;
    bool operator < (const edge &other) const {
        return weight < other.weight;
    }
};
void join(std::vector<int> &a, int q, int w) {
    int x = a[q];
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == x) {
            a[i] = a[w];
        }
    }
}
int kruskal(std::vector<edge> graph, std::vector<int> &a) {
    int fl = 0;
    std::sort(graph.begin(), graph.end());
    for (edge elem : graph) {
        if (a[elem.from] != a[elem.to]) {
            join(a, elem.to, elem.from);
            fl += elem.weight;
        }
    }
    return fl;
}
int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<edge> graph;
    for (int i = 0; i < m; ++i) {
        int a1, b1, c1;
        std::cin >> a1 >> b1 >> c1;
        --a1; --b1;
        graph.push_back({ a1, b1, c1 });
    }
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }
    std::cout<<kruskal(graph, a);
}
 
