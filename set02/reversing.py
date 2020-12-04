#!/usr/bin/python3

import sys

def dfs(graph, curr, visited, out):
    visited.add(curr)
    for v in graph[curr]:
        if v not in visited:
            dfs(graph, v, visited, out)
    out.append(curr)


def components(graph, stack):
    visited = set()
    components = []
    while stack:
        curr = stack.pop()
        out = []
        if curr not in visited:
            dfs(graph, curr, visited, out)
            components.append(set(out))

    return components


def checkComponents(component, graph, inverseGraph):
    inSet = set()
    outSet = set()
    for compoSet in component:
        inRoads = False
        outRoads = False
        for v in compoSet:
            for u in graph[v]:
                outRoads |= u not in compoSet
            for u in inverseGraph[v]:
                inRoads |= u not in compoSet

        if inRoads and not outRoads:
            if inSet != set():
                return (set(), set())
            inSet = compoSet
        if not inRoads and outRoads:
            if outSet != set():
                return (set(), set())
            outSet = compoSet

    return (inSet, outSet)


def findRoad(outComponent, inComponent, graph):
    reversableRoads = set()
    for v in outComponent:
        for u in graph[v]:
            if u in inComponent:
                reversableRoads.add((v, u))

    return reversableRoads


def validate(m, graph, inverseGraph, caseNumber, roads):
    visited = set()
    out = []
    for i in range(len(graph)):
        if i not in visited:
            dfs(graph, i, visited, out)

    component = components(inverseGraph, out)

    if len(component) == 1:
        print("Case ", caseNumber, ": valid", sep = '')
        return

    inComponent, outComponent = checkComponents(component, graph, inverseGraph)
    if outComponent == set() or inComponent == set():
        print("Case ", caseNumber, ": invalid", sep = '')
        return

    reversableRoads = findRoad(outComponent, inComponent, graph) 
    if not reversableRoads:
        print("Case ", caseNumber, ": invalid", sep = '')
        return

    r1 = r2 = -1
    for (tr1, tr2) in roads:
        if (tr1, tr2) in reversableRoads:
            (r1, r2) = (tr1, tr2)
            break

    graph[r1].remove(r2)
    graph[r2].add(r1)
    inverseGraph[r2].remove(r1)
    inverseGraph[r1].add(r2)

    visited = set()
    out = []
    for i in range(len(graph)):
        if i not in visited:
            dfs(graph, i, visited, out)

    component = components(inverseGraph, out)
    if len(component) == 1:
        print("Case ", caseNumber, ": ", r1, " ", r2, sep = '')
    else:
        print("Case ", caseNumber, ": invalid", sep = '')


def createGraph(m, roads, graph, inverseGraph):
    for (r1, r2) in roads:
        graph[r1].add(r2)
        inverseGraph[r2].add(r1)


def main():
    caseNumber = 1
    linesToRead = 0
    m = 0
    roads = []

    for line in sys.stdin:
        numbers = line.split()
        n1 = int(numbers[0])
        n2 = int(numbers[1])
        if linesToRead == 0:
            m = n1
            roads = []
            linesToRead = n2
        else:
            roads.append((n1, n2))
            linesToRead -= 1

        if linesToRead == 0:
            graph = [set() for _ in range(m)]
            inverseGraph = [set() for _ in range(m)]
            createGraph(m, roads, graph, inverseGraph)
            validate(m, graph, inverseGraph, caseNumber, roads)
            caseNumber += 1
            

if __name__ == "__main__":
    main()

