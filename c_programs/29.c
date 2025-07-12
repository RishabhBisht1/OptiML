#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to, w;
    struct Edge *next;
} Edge;

#define N 100
Edge *adj[N];
int dist[N];

void add_edge(int u, int v, int w) {
    Edge *e = malloc(sizeof(Edge));
    e->to = v; e->w = w; e->next = adj[u]; adj[u] = e;
}

void dijkstra(int n, Edge **adj, int src, int *dist) {
    const int INF = 1e9;
    int Q[10000], qn = 0;
    for (int i = 0; i < n; ++i) dist[i] = INF;
    dist[src] = 0;
    Q[qn++] = src;

    for (int qi = 0; qi < qn; ++qi) {
        int u = Q[qi];
        for (Edge* e = adj[u]; e; e = e->next) {
            int v = e->to, nd = dist[u] + e->w;
            if (nd < dist[v]) {
                dist[v] = nd;
                Q[qn++] = v;
            }
        }
    }
}

int main() {
    for (int i = 0; i < N - 1; ++i)
        add_edge(i, i + 1, 1);
    dijkstra(N, adj, 0, dist);
    printf("Shortest path to %d: %d\n", N-1, dist[N-1]);
    return 0;
}
