#include <iostream>
#include <vector>
#include <limits>

class Node {
public:
    Node(int id, long long w, const std::vector<int> &children) 
      : id(id), w(w), children(children)
      , in(w), outDown(std::numeric_limits<long long>::max()), outUp(0) {}

    long long result() const {
        return std::min(in, outDown);
    }

    const std::vector<int> &getChildren() const {
        return children;
    }

    long long getW() const {
        return w;
    }

    long long getIn() const {
        return in;
    }

    long long getOutDown() const {
        return outDown;
    }

    long long getOutUp() const {
        return outUp;
    }

    void setIn(long long val) {
        in = val;
    }
    
    void setOutDown(long long val) {
        outDown = val;
    }

    void setOutUp(long long val) {
        outUp = val;
    }

private:
    bool visited = false;
    int id;
    long long w;
    std::vector<int> children;
    long long in, outDown, outUp;
};

void calculate(Node &node, std::vector<Node> &nodes) {
    if (node.getChildren().empty()) {
        return;
    }

    long long in = node.getW();
    long long outDown = 0;
    long long outUp = 0;
    long long delta = std::numeric_limits<long long>::max();
    for (const int &ch : node.getChildren()) {
        Node &child = nodes[ch];
        calculate(child, nodes);
        in += child.getOutUp();
        outUp += std::min(child.getIn(), child.getOutDown());
        outDown += std::min(child.getIn(), child.getOutDown());
        delta = std::min(delta, std::max(child.getIn() - child.getOutDown(), static_cast<long long>(0)));
    }

    node.setIn(in);
    node.setOutDown(outDown + delta);
    node.setOutUp(outUp);
}

int main(void) {
    int n;
    std::cin >> n;
    std::vector<Node> nodes;
    std::vector<bool> notRoot(n, true);
    for (int i = 0; i < n; i++) {
        long long c, u, child;
        std::cin >> c >> u;
        std::vector<int> children;
        for (long long j = 0; j < u; j++) {
            std::cin >> child;
            children.push_back(child);
            notRoot[child] = false;
        }

        nodes.push_back(Node(i, c, children));
    }

    int root = -1;
    for (int i = 0; i < n; i++) {
        if (notRoot.at(i)) {
            root = i;
            break;
        }
    }
    
    calculate(nodes.at(root), nodes);
    std::cout << nodes.at(root).result() << std::endl;
    return 0;
}

