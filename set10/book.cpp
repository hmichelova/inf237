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
    int b, g;
    std::cin >> b >> g;
    std::vector<std::vector<int>> rgraph(b + g + 2, std::vector<int>()); 
    std::map<std::string, int> boys;
    for (int i = 1; i < b + 1; i++) {
        std::string name;
        long long num;
        std::cin >> name >> num;
        rgraph[0].push_back(i);
        for (int j = 0; j < num; j++) {
            std::string book;
            std::cin >> book;
            boys.insert({book, i});
        }
    }
    
    for (int i = b + 1; i < b + g + 1; i++) {
        std::string name;
        long long num;
        std::cin >> name >> num;
        rgraph[i].push_back(b + g + 1);
        for (int j = 0; j < num; j++) {
            std::string book;
            std::cin >> book;
            rgraph[boys[book]].push_back(i);
        }
    }

    std::cout << calculate(rgraph, b + g + 2) << std::endl;
    return 0;
}

