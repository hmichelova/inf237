#include <iostream>
#include <vector>

int main(void) {
    long long n;
    std::cin >> n;
    long long maximum = 0;
    std::vector<long long> input;
    while (n != 0) {
        if (n > maximum) {
            maximum = n;
        }

        input.push_back(n);
        std::cin >> n;
    }

    std::vector<bool> results((maximum - 1) / 4 + 1, false);
    std::vector<long long> divisors((maximum - 1) / 4 + 1, 1);
    for (long long i = 5; i <= maximum; i += 4) {
        if (divisors.at((i - 1) / 4) != 1) {
            continue;
        }

        long long curr = 5 * i;
        while (curr <= maximum) {
            divisors[(curr - 1) / 4]++;
            if (curr / i <= i && divisors.at((curr / i - 1) / 4) == 1) {
                results[(curr - 1) / 4] = true;
            }
            curr += 4 * i;
        }

    }

    std::vector<long long> res((maximum - 1) / 4 + 1, 0);
    for (long long i = 1; i <= (maximum - 1) / 4; i++) {
        res[i] = res[i - 1] + (results[i] ? 1 : 0);
    }
    
    for (long long i : input) {
        std::cout << i << " " << res[(i - 1) / 4] << std::endl;
    }

    return 0;
}

