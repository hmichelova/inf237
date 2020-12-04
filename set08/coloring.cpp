#include <iostream>
#include <vector>
#include <sstream>

int result;

void calculate(int n, const std::vector<long long> &edges, std::vector<long long> &colors, long long id, int colorCount) {
    if (id >= n) {
        if (result > colorCount) {
            result = colorCount;
        }
        return;
    }

    if (colorCount >= result) {
        return;
    }

    bool change = false;
    for (int i = 0; i < n; i++) {
        if ((edges.at(id) & colors.at(i)) != 0) {
            continue;
        }

        if (colors[i] == 0) {
            change = true;
        }

        colors[i] |= 1 << id;
        calculate(n, edges, colors, id + 1, change ? colorCount + 1 : colorCount);

        colors[i] ^= 1 << id;
        change = false;
    }
}

int main(void) {
    int n;
    std::cin >> n;
    std::vector<long long> edges;
    result = n;

    std::string line;
    std::getline(std::cin, line);
    std::vector<long long> colors;
    for (int i = 0; i < n; i++) {
        std::getline(std::cin, line);
        std::istringstream os(line);
        int j;
        int neigh = 0;
        while (os >> j) {
            if (i == j) {
                continue;
            }

            neigh |= 1 << j;
        }
        edges.push_back(neigh);
        colors.push_back(0);
    }

    colors[0] = 1;

    calculate(n, edges, colors, 1, 1);
    std::cout << result << std::endl;
    return 0;
}

