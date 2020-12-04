#!/usr/bin/python3

import sys

for line in sys.stdin:
    numbers = line.split()
    n0 = int(numbers[0])
    n1 = int(numbers[1])
    print(abs(n0 - n1))

