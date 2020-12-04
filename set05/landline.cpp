#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

class Subset {
public:
    long long parent;
    long long rank;
};

class Edge {
public: 
    Edge(long long s, long long d, long long l) : s(s), d(d), l(l) {}

    long long getS() const { return s; }
    long long getD() const { return d; }
    long long getL() const { return l; }

    static bool comp(const Edge &e1, const Edge &e2) {
        return e1.l < e2.l;
    }

private:
    long long s, d, l;
};

class Graph {
public:
    Graph(long long v, long long e) : v(v), e(e) {}

    void addEdge(long long s, long long d, long long l) {
        Edge edge = Edge(s, d, l);
        edges.push_back(Edge(s, d, l));
        e++;
    }

    void sort() {
        std::sort(edges.begin(), edges.end(), Edge::comp);
    }

    long long calculate() {
        long long size = 0;

        return size;
    }

    long long getV() const {
        return v;
    }

    long long getE() const {
        return e;
    }

    const Edge &getEdge(long long i) const {
        return edges.at(i);
    }

private:
    long long v, e;
    std::vector<Edge> edges;
};

long long find(std::vector<Subset> &subsets, long long i) {
    if (subsets.at(i).parent != i) {
        subsets[i].parent = find(subsets, subsets.at(i).parent);
    }

    return subsets.at(i).parent;
}

void unionSubsets(std::vector<Subset> &subsets, long long x, long long y) {
    long long xRoot = find(subsets, x);
    long long yRoot = find(subsets, y);

    if (subsets.at(xRoot).rank < subsets.at(yRoot).rank) {
        subsets[xRoot].parent = yRoot;
    } else if (subsets.at(yRoot).rank < subsets.at(xRoot).rank) {
        subsets[yRoot].parent = xRoot;
    } else {
        subsets[yRoot].parent = xRoot;
        subsets[xRoot].rank++;
    }
}

long long calculate(Graph &graph, long long n) {
    long long size = 0;

    graph.sort();
    std::vector<Subset> subsets;
    for (long long i = 0; i < n + 1; i++) {
       subsets.push_back({i, 0}); 
    }

    long long indexE = 0;
    long long countV = 0;
    while (countV < graph.getV() - 1 && indexE < graph.getE()) {
        const Edge &edge = graph.getEdge(indexE);
        indexE++;

        long long x = find(subsets, edge.getS());
        long long y = find(subsets, edge.getD());

        if (x != y) {
            size += edge.getL();
            unionSubsets(subsets, x, y);
            countV++;
        }
    }

    if (countV < graph.getV() - 1) {
        return -1;
    }

    return size;
}

int main(void) {
    long long n, m, p;
    std::cin >> n >> m >> p;
    
    std::map<long long, long long> insecure;
    long long num;
    for (long long i = 0; i < p; i++) {
        std::cin >> num;
        insecure.insert({num, 10001});
    }

    if (n == 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    if (n == p) {
        long long x, y, l;
        long long networkSize = 0;
        for (long long i = 0; i < m; i++) {
            std::cin >> x >> y >> l;
            networkSize += l;
        }

        if (m != (n * (n - 1)) / 2) {
            std::cout << "impossible" << std::endl;
            return 0;
        }
        
        std::cout << networkSize << std::endl;
        return 0;
    }

    Graph graph(n - p, 0);
    long long x, y, l;
    for (long long i = 0; i < m; i++) {
        std::cin >> x >> y >> l;
        if (insecure.find(x) != insecure.end()) {
            if (insecure.find(y) == insecure.end()) {
                auto currInsecure = insecure.at(x);
                insecure[x] = std::min(currInsecure, l);
            }
        } else if (insecure.find(y) != insecure.end()) {
            auto currInsecure = insecure.at(y);
            insecure[y] = std::min(currInsecure, l);
        } else {
            graph.addEdge(x, y, l);
        }
    }

    long long networkSize = 0;
    for (const auto &pair : insecure) {
        if (pair.second == 10001) {
            std::cout << "impossible" << std::endl;
            return 0;
        }

        networkSize += pair.second;
    }

    long long size = calculate(graph, n);
    if (size == -1) {
        std::cout << "impossible" << std::endl;
        return 0;
    }

    networkSize += size;
    std::cout << networkSize << std::endl;

    return 0;
}

