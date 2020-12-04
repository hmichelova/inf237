#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <climits>

bool dfs(int curr, std::vector<std::vector<int>> &rgraph, int t, int count, std::vector<bool> &visited) {
    visited[curr] = true;

    if (t == curr) {
        return true;
    }

    for (auto it = rgraph[curr].begin(); it != rgraph[curr].end(); ++it) {
        int v = *it;
        if (visited[v]) {
            continue;
        }
        
        if (dfs(v, rgraph, t, count, visited)) {
            rgraph[curr].erase(it);
            rgraph[v].push_back(curr);
            return true;
        }
    }

    return false;
}

int calculate(std::vector<std::vector<int>> &rgraph, int count) {
    int maxFlow = 0;
    std::vector<bool> visited(count, false);

    while (dfs(0, rgraph, count - 1, count, visited)) {
        visited = std::vector<bool>(count, false);
        maxFlow++;
    }

    return maxFlow;
}

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> rgraph(2 * n + 2, std::vector<int>()); 
    for (int i = 1; i < m + 1; i++) {
        long long a, b;
        std::cin >> a >> b;
        rgraph[a].push_back(n + b);
        rgraph[b].push_back(n + a);
    }
    
    for (int i = 1; i < n + 1; i++) {
        rgraph[0].push_back(i);
        rgraph[n + i].push_back(2 * n + 1);
    }

    long long flow = calculate(rgraph, 2 * n + 2);
    if (flow != n) {
        std::cout << "Impossible" << std::endl;
        return 0;
    }

    std::vector<int> results(n, -1);
    for (int i = n + 1; i < 2 * n + 1; i++) {
        results[rgraph[i][0] - 1] = i - n;
    }

    for (int i : results) {
        std::cout << i << std::endl;
    }

    return 0;
}

