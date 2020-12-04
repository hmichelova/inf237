#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Storage {
public:
    Storage(long long index) : index(index) {
    }

    long long getChildren(char c) const {
        return children.at(c - 'a');
    }

    long long getPrefix(long long count) const {
        if (count == 0) {
            return -1;
        }

        return prefix + ((count - 1) % words);
    }

    std::vector<long long> children { -1, -1, -1, -1, -1, -1
        , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
        , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    long long prefix = -1;
    long long words = 0;
    long long index;
    
};

long long addWord(const std::string &w, long long wIndex, long long wLength
    , std::vector<Storage> &nodes, long long length, long long currIndex, 
    std::vector<std::pair<std::string, long long>> &input, long long inputIndex) {
    Storage &curr = nodes[currIndex];

    if (wIndex == wLength) {
        curr.words++;
        input[inputIndex] = { input[inputIndex].first, curr.index };
        return inputIndex;
    }

    long long newLength = length;
    if (curr.children.at(w[wIndex] - 'a') == -1) {
        newLength++;
        nodes.push_back(Storage(length));
        nodes[currIndex].children[w[wIndex] - 'a'] = length;
    }

    auto rv = addWord(w, wIndex + 1, wLength, nodes, newLength, nodes[currIndex].children[w[wIndex] - 'a'], input, inputIndex);
    nodes[currIndex].words++;

    if (nodes[currIndex].prefix == -1) {
        nodes[currIndex].prefix = rv;
    }
    return rv;
}

long long hashClicked(std::vector<Storage> &nodes, long long nodeIndex
    , long long hashCount, std::string &result
    , std::vector<std::pair<std::string, long long>> &input) {
    if (hashCount == 0) {
        return nodeIndex;
    }

    if (nodeIndex == -1) {
        return -1;
    }

    long long rv = nodes[nodeIndex].getPrefix(hashCount);
    if (rv != -1) {
        result = input.at(rv).first;
        return input.at(rv).second;
    }

    return rv;
}

void calculate(std::vector<Storage> &nodes, const std::string &word
    , std::vector<std::pair<std::string, long long>> &input) {
    std::string result;
    long long nodeIndex = 0;
    long long count = 0;

    for (char c : word) {
        if (c == '#') {
            count++;
        } else {
            nodeIndex = hashClicked(nodes, nodeIndex, count, result, input);
            count = 0;
            result += c;
            if (nodeIndex != -1) {
                nodeIndex = nodes[nodeIndex].getChildren(c);
            }
        }
    }
    
    nodeIndex = hashClicked(nodes, nodeIndex, count, result, input);
    count = 0;

    std::cout << result << std::endl;
}

int main(void) {
    long long n;
    std::cin >> n;
    std::vector<std::pair<std::string, long long>> input;
    for (long long i = 0; i < n; i++) {
        std::string word;
        std::cin >> word;
        input.push_back({word, -1});
    }

    std::sort(input.begin(), input.end());

    std::vector<Storage> nodes;
    nodes.push_back(Storage(0));
    for (int i = 0; i < n; i++) {
        addWord(input[i].first, 0, input[i].first.length(), nodes, nodes.size(), 0, input, i);
    }

    long long r;
    std::cin >> r;
    for (long long i = 0; i < r; i++) {
        std::string word;
        std::cin >> word;
        calculate(nodes, word, input);
    }
    
    return 0;
}

