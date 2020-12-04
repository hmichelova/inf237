#!/usr/bin/python3

def isOut(i, j, h, w, side):
    x, y = neighbour(i, j, side)
    return x < 0 or x >= h or y < 0 or y >= w



def neighbour(i, j, side):
    if side == 0:
        return i - 1, j

    if side == 1:
        return i, j + 1

    if side == 2:
        return i + 1, j

    return i, j - 1



def createGraph(h, w, hexGraph, graph):
    fstOut = sndOut = -1
    haveFirst = False
    for i in range(h):
        for j in range(w):
            binNumber = bin(int(hexGraph[i][j], 16))[2:]
            binNumber = '0' * (4 - len(binNumber)) + binNumber
            for side in range(1, 3):
                if binNumber[side] == '0':
                    if isOut(i, j, h, w, side):
                        if fstOut == -1:
                            fstOut = i * w + j
                        else:
                            sndOut = i * w + j
                    else:
                        x, y = neighbour(i, j, side)
                        graph[i * w + j].add(x * w + y)
                        graph[x * w + y].add(i * w + j)

            if (i == 0 and binNumber[0] == '0') or (j == 0 and binNumber[3] == '0'):
                if fstOut == -1:
                    fstOut = i * w + j
                else:
                    sndOut = i * w + j

    return (fstOut, sndOut)



def dfs(graph, start):
    visited = set()
    stack = [start]
    multiplePath = False
    while stack:
        curr = stack.pop()
        if curr not in visited:
            visited.add(curr)
            stack.extend(graph[curr] - visited)
        else: 
            multiplePath = True

    return visited, multiplePath



def processOne():
    size = input().split()
    h = int(size[0])
    w = int(size[1])
    if h == 0 and w == 0:
        return True

    hexGraph = []

    for i in range(h):
        hexGraph.append(input())

    graph = [set() for x in range(w * h)]
    fstOut, sndOut = createGraph(h, w, hexGraph, graph)

    visited, multiplePath = dfs(graph, fstOut)

    if sndOut not in visited:
        print("NO SOLUTION")
    elif len(visited) != h * w:
        print("UNREACHABLE CELL")
    elif multiplePath:
        print("MULTIPLE PATHS")
    else:
        print("MAZE OK")

    return False



def main():
    lastGraph = False
    while not lastGraph:
        lastGraph = processOne()


main()

