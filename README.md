# Iterative Depth-First Search (DFS) in C++

This project implements an **iterative DFS** (Depth-First Search).

---

## Features
- Iterative DFS using a stack
- **Discovery**, **Finishing times** and **Parents** for each vertex
- Reads graph from standard input
- Prints results to standard output

---

## Input Format
The program reads a 0 indexed graph in **adjacency list format**:
```
numberOfVertices numberOfVerticesWithAdjacencies isDirectedGraph(1/0)

vertexID Degree neighbor1 neighbor2 ...

...
```

### Example
```
8 6 1
0 1 2
1 2 2 5
2 2 0 6
4 2 6 7
5 1 6
6 2 2 5
```
![Example DFS](https://github.com/nuno-lucio/Iterative-DFS/raw/master/examples/example_graph.png)

---

## Build
```
g++ -std=c++11 -O3 -Wall main.cpp -o DFS
```

---

## Run
```
./DFS < graph.txt
```
