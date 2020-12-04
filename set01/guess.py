#!/usr/bin/python3

import sys

def middle(x, y):
    return (x + y) // 2

def guess(down, up):
    mid = middle(down, up)
    print(mid)
    answer = input()

    if answer == "correct":
        return 0

    if answer == "lower":
        guess(down, mid)
    else:
        guess(mid, up)

guess(1, 1001)

