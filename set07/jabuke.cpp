#include <iostream>
#include <iomanip>

long long area(long long xa, long long ya, long long xb, long long yb
    , long long xc, long long yc) {
    return std::abs(xa * (yb - yc) + xb * (yc - ya) + xc * (ya - yb));
}

int isInside(long long xa, long long ya, long long xb, long long yb
    , long long xc, long long yc, long long x, long long y, long long abcArea) {
    long long abpArea = area(xa, ya, xb, yb, x, y);
    long long acpArea = area(xa, ya, xc, yc, x, y);
    long long bcpArea = area(xb, yb, xc, yc, x, y);

    return abcArea == abpArea + acpArea + bcpArea ? 1 : 0;
}

int main(void) {
    long long xa, xb, xc, ya, yb, yc, n;
    std::cin >> xa >> ya;
    std::cin >> xb >> yb;
    std::cin >> xc >> yc;

    long long abcArea = area(xa, ya, xb, yb, xc, yc);
    std::cout.precision(1);
    std::cout << std::fixed << abcArea / static_cast<double>(2) << std::endl;

    std::cin >> n;
    long long x, y;
    long long count = 0;
    for (long long i = 0; i < n; i++) {
        std::cin >> x >> y;
        count += isInside(xa, ya, xb, yb, xc, yc, x, y, abcArea);
    }

    std::cout << count << std::endl;
    
    return 0;
}

