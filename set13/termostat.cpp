#include <iostream>
#include <vector>
#include <algorithm>

void calculate(const std::vector<std::pair<long long, long long>> &systems, long long x, long long y, long long v) {
    long long denominator = systems.at(x).second - systems.at(x).first;
    long long numerator = (v - systems.at(x).first) * (systems.at(y).second - systems.at(y).first) 
      + systems.at(y).first * denominator;

    if (numerator == 0) {
        std::cout << "0/1" << std::endl;
        return;
    }

    long long gcd = std::__gcd(std::abs(denominator), std::abs(numerator));
    denominator /= gcd;
    numerator /= gcd;

    if ((denominator < 0 && numerator > 0) || (denominator > 0 && numerator < 0)) {
        std::cout << "-";
    }

    std::cout << std::abs(numerator) << "/" << std::abs(denominator) << std::endl;
}

int main(void) {
    long long n, q;
    std::cin >> n >> q;
    std::vector<std::pair<long long, long long>> systems;
    for (long long i = 0; i < n; i++) {
        long long a, b;
        std::cin >> a >> b;
        systems.push_back({a, b});
    }

    for (long long i = 0; i < q; i++) {
        long long x, y, v;
        std::cin >> x >> y >> v;
        calculate(systems, x - 1, y - 1, v);
    }

    return 0;
}

