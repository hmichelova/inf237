#!/usr/bin/python3

import sys

def calculate(n, w1, maximum):
    startIndex = 0

    for currIndex in range(1, n):
        if w1[startIndex] < maximum:
            startIndex = currIndex
            continue

        if w1[startIndex] == w1[currIndex]:
            if startIndex != currIndex:
                startIndex = currIndex + 1
        elif w1[startIndex] < w1[currIndex]:
            maximum = w1[startIndex]
            startIndex = currIndex
        elif w1[currIndex] > maximum:
            maximum = w1[currIndex]

    if startIndex < n:
        maximum = max(maximum, w1[startIndex])

    return maximum


def main():
    n = int(input())

    w1 = [int(i) for i in input().split()]
    w2 = [int(i) for i in input().split()]

    if n == 1:
        print(w1[0])
        return

    rv = calculate(n, w1, 0)
    rv = calculate(n, w2, rv)
    print(rv)


if __name__ == "__main__":
    main()

