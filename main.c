#include "search.h"
#include "stats.h"
#include "draw.h"
#include "mylib.h" 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int   op = 0; // 表示输入的参数所代表的操作
    int   temp; // 临时变量，用来存储中间量 
    int   result_int;
    float result_float;
    char *result_char;
    
    //测试 
    /*for (int i = 0; i < 19; i++) {
        printf("%s\n", SunTou[i]);
    }*/
    
    /*for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }*/ 
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            op = 1; // op为1，输出帮助菜单 
        } else if (strcmp(argv[1], "-j") == 0) {
            for (int i = 0; i < 19; i++) {
                printf("%s\n", SunTou[i]);
            }
        }
    } else if (argc == 5 || argc == 6) {
        if (strcmp(argv[3], "-s") == 0 || strcmp(argv[3], "--stats")== 0) {
            op = 2; // edges, vertices, freeman, closeness
        } 
    } else if (argc == 9) {
        if (strcmp(argv[3], "-sp") == 0 || strcmp(argv[3], "shortestpath") == 0) {
            op = 3;
        }
    }
    
    switch(op) {
        case 0:
            printf("Not Found The Command.\n");
            break;
        
        case 1:
            print_help_order();
            break;
        
        case 2:
            if (strcmp(argv[4], "edges") == 0) {
                result_int = numberOfEdges(argv[2]);
                printf("the number of edges is %d\n", result_int);
            } else if (strcmp(argv[4], "vertices") == 0) {
                result_int = numberOfVertices(argv[2]);
                printf("the number of vertices is %d\n", result_int);
            } else if (strcmp(argv[4], "freeman") == 0) {
                result_float = freemanNetworkCentrality(argv[2]);
                printf("the Freeman's Network Centrality is %f\n", result_float);
            } else if (strcmp(argv[4], "closeness") == 0) {
                temp = (int)(argv[5] - '0');
                result_float = closenessCentrality(argv[2], temp);
                printf("the Closeness Centrality is %f\n", result_float);
            } else {
                printf("Not Found The Command.\n");
            }
            break;
        
        case 3:
            if (strcmp(argv[4], "DFS") == 0 || strcmp(argv[4], "BFS") == 0 || strcmp(argv[4], "Dijkstra") == 0) {
                int u = (int)(*argv[6] - '0');
                int v = (int)(*argv[8] - '0');
                result_char = shortestPath(u, v, argv[4], argv[2]);
                printf("%s", result_char);
            } else {
                printf("Not Found the Command.\n");
            }
            break;
    }
    return 0;
}
