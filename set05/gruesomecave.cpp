#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <set>
#include <map>
#include <queue>

class Node {
public: 
    Node(long long id) : id(id) {}

    static bool comp(const Node *n1, const Node *n2) {
        return n1->getDistance() < n2->getDistance();
    }

    long long getId() const {
        return id;
    }

    long long getDistance() const {
        return distance;
    }

    std::vector<std::pair<Node *, long long>> &getEdges() {
        return edges;
    }

    void addEdge(Node *end, long long l) {
        edges.push_back({end, l});
    }

    void setFinished(bool fin) {
        finished = fin;
    }

    bool isFinished() const {
        return finished;
    }

    bool updateDistance(long long newDist) {
        if (newDist < distance) {
            distance = newDist;
            return true;
        }

        return false;
    }

    bool getIsInQueue() const {
        return isInQueue;
    }

    void pushedToQueue() {
        isInQueue = true;
    }

private:
    long long id;
    long long distance = std::numeric_limits<long long>::max();
    std::vector<std::pair<Node *, long long>> edges;
    bool finished = false;
    bool isInQueue = false;
};

class Graph {
public:
    Graph() : e(0) { }

    void addEdge(long long s, long long d, long long l, bool count) {
        if (nodes.find(s) == nodes.end()) {
            nodes.insert({s, new Node(s)});
        }
        
        if (nodes.find(d) == nodes.end()) {
            nodes.insert({d, new Node(d)});
        }
        nodes.at(s)->addEdge(nodes.at(d), l);

        if (count) {
            e++;
        }
    }

    long long getE() const {
        return e;
    }

    Node *getNode(long long index) {
        return nodes.at(index);
    }

private:
    long long len, e;
    std::map<long long, Node *> nodes;
};

void addEdges(Graph &graph, const std::vector<std::string> &cave
    , long long i, long long j, long long index, long long w) {
    std::vector<std::pair<long long, bool>> neigh;
    bool isSpace = cave.at(i).at(j) != 'E' && cave.at(i).at(j) != 'D';
    int len = 0;
    for (int indexI = -1; indexI <= 1; indexI++) {
        for (int indexJ = -1; indexJ <= 1; indexJ++) {
            if ((indexI != 0 && indexJ != 0) || indexI == indexJ 
            || cave.at(i + indexI).at(j + indexJ) == '#') {
                continue;
            }

            bool s = cave.at(i + indexI).at(j + indexJ) != 'E' && cave.at(i + indexI).at(j + indexJ) != 'D';
            if (s && isSpace) {
                len++;
            }
            neigh.push_back({index + indexI * w + indexJ, s});
        }
    }

    for (const auto &pair : neigh) {
        graph.addEdge(pair.first, index, len, isSpace && pair.second);
    }
}

long long calculate(Graph &graph, long long e, long long d) {
    auto cmp = [] (const Node *n1, const Node *n2) { return n1->getDistance() > n2->getDistance(); };
    std::priority_queue<Node *, std::vector<Node *>, decltype(cmp)> toProcess(cmp);
    Node *nodeE = graph.getNode(e);
    nodeE->updateDistance(0);
    nodeE->pushedToQueue();
    toProcess.push(nodeE);

    while (!toProcess.empty()) {
        Node *node = toProcess.top();
        toProcess.pop();
        if (node->getId() == d) {
            return node->getDistance();
        }

        long long dist = node->getDistance();
        for (auto &pair : node->getEdges()) {
            if (!pair.first->isFinished()) {
                bool shouldPush = pair.first->updateDistance(dist + pair.second);
                if (shouldPush && !pair.first->getIsInQueue()) {
                    pair.first->pushedToQueue();
                    toProcess.push(pair.first);
                }
            }
        }

        node->setFinished(true);
    }

    return -1;
}

int main(void) {
    long long l, w;
    std::cin >> l >> w;
    
    std::vector<std::string> cave;
    std::string line;
    std::getline(std::cin, line);
    std::string line2 = "";
    for (long long j = 0; j < w + 2; j++) {
        line2.push_back('#');
    }

    cave.push_back(line2);
    for (long long i = 0; i < l; i++) {
        std::getline(std::cin, line);
        line.push_back('#');
        line.insert(0, "#");
        cave.push_back(line);
    }
    cave.push_back(line2);

    Graph graph;
    long long e = -1;
    long long d = -1;
    for (long long i = 1; i <= l; i++) {
        for (long long j = 1; j <= w; j++) {
            long long index = i * w + j;
            if (cave.at(i).at(j) == 'E') {
                e = index;
                addEdges(graph, cave, i, j, index, w);
            } else if (cave.at(i).at(j) == ' ') {
                addEdges(graph, cave, i, j, index, w);
            } else if (cave.at(i).at(j) == 'D') {
                d = index;
                addEdges(graph, cave, i, j, index, w);
            }
        }
    }

    long long length = calculate(graph, e, d);
    long long edgeCount = graph.getE();
    std::cout << length / static_cast<double>(edgeCount) << std::endl;

    return 0;
}

