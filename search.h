#ifndef SEARCH_H
#define SEARCH_H

char* shortestPath(int u, int v, char algorithm[], char name[]);

void DFS(AdjGraph* G, int u, int v, int d);


void Dijkstra(AdjGraph g, int u, int v);
#endif

