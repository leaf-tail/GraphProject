#include "search.h"
#include <stdio.h>
#include <stdlib.h>

int strcmp(const char *s1, const char *s2)
{
    for (; *s1 == *s2; s1++, s2++) {
        if (*s1 == '\0') {
            return 0;
        }
    }
    return *(unsigned char *)s1 < *(unsigned char*)s2 ? -1 : 1;
}

char* shortestPath(int u, int v, char alogrithm[], char name[])
{
    char *t = "test";
    return t;
}

void print_help_order()
{
    printf("    -g/--graph FILE_PATH \n");
    printf("                         -s/--stats edges\n\n");
    printf("        print the edges of a graph.\n\n");
    printf("                        -s/--stats vertices\n\n");
    printf("        print the vertices of a graph.\n\n");
    printf("                         -s/--stats freeman\n\n");
    printf("        print the Freeman's Network Centrality.\n\n");
    printf("                         -s/--stats closeness\n\n");
    printf("        print the Closeness Centrality.\n\n");
    printf("\n");
    printf("                        -sp/--shortestpath\n\n");
    printf("                                    DFS\n\n");
    printf("                                    BFS\n\n");
    printf("                                    Dijkstra\n\n");
    return; 
}
