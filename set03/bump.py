#!/usr/bin/python3

import sys

def calculate(x1, x2, n1, n2, c1, c2):
    t = 0
    s1 = 0
    s2 = 0
    curr1 = 0
    curr2 = 0
    while curr1 < c1 or curr2 < c2:
        if x1 >= x2:
            print("bumper tap at time", t)
            return

        if curr1 < c1 and n1[curr1] == t:
            s1 += 1
            s1 %= 2
            curr1 += 1

        if curr2 < c2 and n2[curr2] == t:
            s2 += 1
            s2 %= 2
            curr2 += 1
        
        t += 1
        x1 += s1
        x2 += s2

    if s1 == 1 and s2 == 0:
        print("bumper tap at time", int(t + x2 - x1 + 1))
    else: 
        print("safe and sound")




def main():
    line = input().split()
    x1 = int(line[0])
    x2 = int(line[1])

    n1 = [int(i) for i in input().split()]
    c1 = n1.pop(0)
    n2 = [int(i) for i in input().split()]
    c2 = n2.pop(0)

    if x1 < x2:
        calculate(x1 + 4.4, x2, n1, n2, c1, c2)
    else:
        calculate(x2 + 4.4, x1, n2, n1, c2, c1)


if __name__ == "__main__":
    main()

