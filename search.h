#include "stats.h"

#ifndef GRAPH_SEARCH_H_
#define GRAPH_SEARCH_H_
char* shortestPath(int u, int v, char algorithm[], char name[]);
char* BFS(int u, int v, char name[], AdjGraph *G); 
#endif
