#include <iostream>
#include <algorithm>
#include <vector>

long long createTree(long long n, std::vector<long long> &segmentTree) {
    n += 2;
    long long count = 1;
    while (count < n) {
        count *= 2;
    }
    count *= 2;
    for (long long i = 0; i < count; i++) {
        segmentTree.push_back(0);
    }

    return count / 2;
}

void flipQuery(long long i, std::vector<long long> &segmentTree, long long n) {
    int change = 1;
    long long pos = n + i;
    if (segmentTree.at(n + i) == 1) {
        change = -1;
    }
    
    while (pos > 0) {
        segmentTree[pos] += change;
        pos /= 2;
    }
}

long long countQuery(long long l, long long r
    , const std::vector<long long> &segmentTree, long long n) {
    long long left = l + n - 1;
    long long right = r + n + 1;
    long long rv = 0;

    while (true) {
        bool lr = (left % 2) == 0;
        bool rl = (right % 2) == 1;
        left /= 2;
        right /= 2;
        if (left == right) {
            break;
        }

        if (lr) {
            rv += segmentTree[2 * left + 1];
        }
        if (rl) {
            rv += segmentTree[2 * right];
        }
    }

    return rv;
}

int main(void) {
    long long n, k;
    std::cin >> n >> k;

    std::vector<long long> segmentTree;
    n = createTree(n, segmentTree);

    char query;
    long long l, r;
    for (long long i = 0; i < k; i++) {
        std::cin >> query;
        if (query == 'F') {
            std::cin >> l;
            flipQuery(l, segmentTree, n);
        } else {
            std::cin >> l >> r;
            std::cout << countQuery(l, r, segmentTree, n) << std::endl;
        }
    }
    
    return 0;
}

