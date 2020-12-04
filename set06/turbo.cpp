#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

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

void flipQuery(long long i, std::vector<long long> &segmentTree, long long off) {
    int change = 1;
    long long pos = off + i;
    
    while (pos > 0) {
        segmentTree[pos] += change;
        pos /= 2;
    }
}

long long countQuery(long long l, long long r
    , const std::vector<long long> &segmentTree, long long off) {
    long long left = l + off - 1;
    long long right = r + off + 1;
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
    long long n;
    std::cin >> n;

    std::vector<long long> segmentTreeHigher;
    std::vector<long long> segmentTreeLower;
    createTree(n, segmentTreeHigher);
    long long off = createTree(n, segmentTreeLower);

    std::vector<long long> numbers;
    for (long long i = 0; i < n; i++) {
        long long num;
        std::cin >> num;
        numbers.push_back(num);
    }

    std::map<long long, long long> res;
    double mid = (n + 1) / static_cast<double>(2);
    for (long long num : numbers) {
        if (num < mid) {
            res.insert({num, countQuery(num, n - num + 1, segmentTreeHigher, off)});
        } else if (num == mid) {
            res.insert({num, 0});
        }
        
        flipQuery(num, segmentTreeHigher, off);
    }

    for (auto num = numbers.rbegin(); num != numbers.rend(); num++) {
        if (*num > mid) {
            res.insert({*num, countQuery(n - *num + 2, *num, segmentTreeLower, off)});
        }
        
        flipQuery(*num, segmentTreeLower, off);
    }

    for (long long i = 1; i <= mid; i++) {
        std::cout << res.at(i) << std::endl;
        if (n - i + 1 != i) {
            std::cout << res.at(n - i + 1) << std::endl;
        }
    }
    
    return 0;
}

