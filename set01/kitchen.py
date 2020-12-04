#!/usr/bin/python3

import sys

def calculate(s, m, d, brands, ingr, incompatible):
    result = 0
    for sd in range(1, s + 1):
        ingredientsSD = ingr[sd]
        for md in range(s + 1, s + m + 1):
            ingredientsMD = ingredientsSD.union(ingr[md])
            for dd in range(s + m + 1, s + m + d + 1):
                ingredients = ingredientsMD.union(ingr[dd])
                if md not in incompatible[sd] and dd not in incompatible[sd] and dd not in incompatible[md]:
                    curr = 1
                    for i in ingredients:
                        curr *= brands[i]
                    result += curr
                    if result > 10 ** 18 or result < 0:
                        print("too many")
                        return

    print(result)


def main():
    line = input().split()
    r = int(line[0])
    s = int(line[1])
    m = int(line[2])
    d = int(line[3])
    n = int(line[4])

    brands = [int(i) for i in input().split()]
    brands.insert(0, 0)
    ingr = [set() for _ in range(s + m + d + 1)]
    incompatible = [set() for _ in range(s + m + d + 1)]

    for i in range(1, s + m + d + 1):
        l = [int(ing) for ing in input().split()]
        l.pop(0)
        ingr[i] = set(l)

    for i in range(n):
        l = input().split()
        m1 = int(l[0])
        m2 = int(l[1])
        incompatible[m1].add(m2)
        incompatible[m2].add(m1)

    calculate(s, m, d, brands, ingr, incompatible)


if __name__ == "__main__":
    main()

