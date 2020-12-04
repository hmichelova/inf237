#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <set>
#include <map>


using element = long long;
using table = std::vector<std::vector<element>>;

void addResult(const element &res, const std::vector<long long> &order
    , long long index
    , std::vector<std::string> &results) {
    if (res == 0) {
        results[index] = "Impossible";
    } else if (res >= 2) {
        results[index] = "Ambiguous";
    } else {
        std::stringstream ss;
        std::string sep = "";
        for (auto i : order) {
            ss << sep << i;
            sep = " ";
        }
        results[index] = ss.str();
    }
}

void addResults(long long o, long long n, long long m
    , const std::vector<long long> &costs
    , const std::vector<long long> &orders
    , const element &res
    , std::vector<std::string> &results
    , const table &optionsPairs) {
    for (long long i = 0; i < m; i++) {
        if (orders[i] == o) {
            std::vector<long long> order;
            if (res == 1) {
                long long currCol = n - 1;
                long long currRow = o;
                while (currRow > 0) {
                    if (currCol == 0) {
                        order.push_back(currCol + 1);
                        currRow -= costs[currCol];
                    } else {
                        if (optionsPairs[currRow][currCol - 1] == 1) {
                            currCol -= 1;
                        } else {
                            order.push_back(currCol + 1);
                            currRow -= costs[currCol];
                        }
                    }
                }
                std::reverse(order.begin(), order.end());
            }

            addResult(res, order, i, results);
        }
    }
}

element calcValue(long long row, long long column, long long cost
    , const table &optionsPairs, const std::vector<element> &prev) {
    long long options = 0;
    if (column > 0 && options < 2) {
        const auto &other = prev.at(column - 1);
        options += other;
    }

    if (options < 2) {
        long long smaller = optionsPairs[row][column];
        options += smaller;
    }

    return options;
}

void calculate(long long n, long long m, long long maxCost, long long maxOrder
    , table &optionsPairs
    , std::vector<long long> costs
    , std::vector<long long> orders
    , std::vector<std::string> &results) {
    bool removeLine = false;
    long long rowCount = std::max(static_cast<long long>(300000), maxCost);
    for (long long i = 0; i < maxOrder + 1; i++) {
        std::vector<element> line;
        for (long long j = 0; j < n; j++) {
            if (i < costs[j]) {
                if (j == 0) {
                    line.push_back(0);
                } else {
                    line.push_back(line.back());
                }
            } else {
                long long index = i;
                if (removeLine) {
                    index = rowCount;
                }
                auto rv = calcValue(index - costs[j], j
                    , costs[j], optionsPairs, line);
                if (i == costs[j]) {
                    if (rv == 0) {
                        rv = 1;
                    } else {
                        rv += 1;
                    }
                }
                line.push_back(rv);
            }
        }
        optionsPairs.push_back(line);
        removeLine = i >= rowCount;
        if (removeLine) {
            optionsPairs.erase(optionsPairs.begin());
        }

        addResults(i, n, m, costs, orders, line.at(n - 1), results, optionsPairs);
    }
}

int main(void) {
    long long n, m;
    std::cin >> n;
    std::string line;
    std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::istringstream iss(line);
    long long num;
    std::vector<long long> costs;
    while (iss >> num) {
        costs.push_back(num);
    }

    std::cin >> m;
    std::string line2;
    std::getline(std::cin, line2);
    std::getline(std::cin, line2);
    std::istringstream iss2(line2);
    std::vector<long long> orders;
    std::vector<std::string> results;
    while (iss2 >> num) {
        results.push_back("");
        orders.push_back(num);
    }

    long long maxCost = *std::max_element(costs.begin(), costs.end());
    long long maxOrder = *std::max_element(orders.begin(), orders.end());

    table optionsPairs;

    calculate(n, m, maxCost, maxOrder, optionsPairs, costs, orders, results);

    for (const auto &result : results) {
        std::cout << result << std::endl;
    }

    return 0;
}

