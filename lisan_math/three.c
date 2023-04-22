// To solve the traveling salesman problem, we need to find the minimum weight of the Hamiltonian cycle in the weighted graph.
// The distance between vertex u and vertex v is r, and the weight of connecting u and v is r.
// The weight of a circle C in the graph refers to the sum of the weights of all edges in C.
// In order to solve the traveling salesman problem, we need to determine the minimum weight of the Hamiltonian cycle in the weighted graph.
// For example, if a salesman plans to travel between some cities, the distance between cities is the weighted graph G shown in the figure. 
// Then what is the minimum distance of his trip this time?
// Because G is a 5-order graph, there are (5-1)!/2=12 Hamiltonian cycles in G, and each cycle and its weight list are as follows:
// Hamiltonian cycle
// Weight of the cycle

// S1=(C1,C2,C3,C4,C5,C1)
// 7+10+8+6+12=43

// S2=(C1,C2,C3,C5,C4,C1)
// 7+10+4+6+9=36

// S3 = (C1,C2,C4,C3,C5,C1)
// 44

// S4=(C1,C2,C4,C5,C3,C1)
// 41

// S5=(C1,C2,C5,C3,C4,C1)
// 42

// S6=(C1,C2,C5,C4,C3,C1)
// 46

// S7=(C1,C3,C2,C4,C5,C1)
// 52

// S8=(C1,C3,C2,C5,C4,C1)
// 50

// S9=(C1,C3,C4,C2,C5,C1)
// 58

// S10=(C1,C3,C5,C2,C4,C1)
// 51

// S11=(C1,C4,C2,C3,C5,C1)
// 48

// S12=(C1,C4,C3,C2,C5,C1)
// 53

// Here is a C code to solve the traveling salesman problem using brute force approach:

#include <stdio.h>
#include <limits.h>

#define V 5 // number of vertices in the graph

int graph[V][V] = { { 0, 7, 10, INT_MAX, 8 },
                    { 7, 0, 4, 6, INT_MAX },
                    { 10, 4, 0, 12, 6 },
                    { INT_MAX, 6, 12, 0, 9 },
                    { 8, INT_MAX, 6, 9, 0 } }; // adjacency matrix representation of the graph

int visited[V]; // to keep track of visited vertices
int min_cost = INT_MAX; // to store the minimum cost of the Hamiltonian cycle

void tsp(int curr_vertex, int count, int cost) {
    if (count == V && graph[curr_vertex][0]) { // if all vertices have been visited and there is an edge from the last vertex to the starting vertex
        min_cost = (cost + graph[curr_vertex][0] < min_cost) ? cost + graph[curr_vertex][0] : min_cost; // update the minimum cost
        return;
    }
    for (int i = 0; i < V; i++) {
        if (!visited[i] && graph[curr_vertex][i]) { // if the vertex has not been visited and there is an edge from the current vertex to the next vertex
            visited[i] = 1; // mark the vertex as visited
            tsp(i, count + 1, cost + graph[curr_vertex][i]); // recursively call the function for the next vertex
            visited[i] = 0; // unmark the vertex as visited
        }
    }
}

int main() {
    visited[0] = 1; // mark the starting vertex as visited
    tsp(0, 1, 0); // call the tsp function with the starting vertex, count = 1, and cost = 0
    printf("Minimum cost of the Hamiltonian cycle: %d\n", min_cost); // print the minimum cost of the Hamiltonian cycle
    return 0;
}