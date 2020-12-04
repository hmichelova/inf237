#include <iostream>

long long constructPalyndrome(long long base, long long toSwap) {
    while (toSwap > 0) {
        base *= 2;
        base += toSwap % 2;
        toSwap /= 2;
    }
    
    return base;
}

int main(void) {
    long long n;
    std::cin >> n;
    if (n == 1) {
        std::cout << 1 << std::endl;
        return 0;
    }

    long long length = (n + 1) / 3;
    long long powerTwo = 1;
    while (powerTwo <= length) {
        powerTwo *= 2;
    }
    powerTwo /= 2;

    long long start = powerTwo * 3 - 1;

    long long result = 0;
    if (n < start + powerTwo) {
        long long base = powerTwo + n - start;
        result = constructPalyndrome(base, base);
    } else {
        long long base = powerTwo * 2 + n - start - powerTwo;
        result = constructPalyndrome(base, base / 2);
    }

    std::cout << result << std::endl;    
    return 0;
}

