#include "search.h"
#include "stats.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>

int visited[MAX];
int path_DFS[MAX];      //DFS算法中纪录路径的数组
int path_putout_DFS[MAX];

int path_Dij[MAX];//最短长度数组，路径数组
int dist[MAX];//最短路径长度数组
int S[MAX];//标记数组
int path_putout_Dij[MAX];

char* shortestPath(int u, int v, char alogrithm[], char name[])
{
    AdjGraph *G;
    G = CreateAdj(name);
    char *res;
    
    for (int i = 0; i < MAX; i++) { //初始化全局标记数组
        visited[i] = 0; 
    }
    
    if (strcmp(alogrithm, "DFS") == 0) {
        DFS(G, u, v, -1);
        int  j = 0;
        char tem_str[500];
        int  count_len;
        int  temindex = 0;
        for (int i = 1; i <= path_putout_DFS[0]; i++) {
            count_len = 0;
            int tempn = path_putout_DFS[i];
            if (tempn == 0) {
                tem_str[500] = '0';
                count_len++;
            }
            while (tempn != 0) {
                tem_str[count_len] = tempn % 10 + '0';
                tempn = tempn / 10;
                count_len++;
            }
            while (count_len > 0) {
                res[temindex] = tem_str[count_len - 1];
                temindex++;
                count_len--;
            }
            if (j > 0) {
                res[temindex] = '-';
                temindex++;
                res[temindex] = '>';
                temindex++;
            }
        }
        res[temindex] = '\0';
    } else if (strcmp(alogrithm, "BFS") == 0) {
        //DispAdj(G);
        G = TransformGraph(G);
        //DispAdj(G);
        res = BFS(u, v, name, G);
    } else {
        Dijkstra(G, u, v);
        int  j = 0;
        char tem_str[500];
        int  count_len;
        int  temindex = 0;
        for (int i = 1; i <= path_putout_Dij[0]; i++) {
            count_len = 0;
            int tempn = path_putout_Dij[i];
            if (tempn == 0) {
                tem_str[500] = '0';
                count_len++;
            }
            while (tempn != 0) {
                tem_str[count_len] = tempn % 10 + '0';
                tempn = tempn / 10;
                count_len++;
            }
            while (count_len > 0) {
                res[temindex] = tem_str[count_len - 1];
                temindex++;
                count_len--;
            }
            if (j > 0) {
                res[temindex] = '-';
                temindex++;
                res[temindex] = '>';
                temindex++;
            }
        }
        res[temindex] = '\0';
    }
      
    return res;
}

char* BFS(int u, int v, char name[], AdjGraph *G)
{
    int   index;
    int   flag = 0;
    char *res;
    int  *pres;
    res = (char *)malloc(sizeof(char) * MAX); //储存路径 
    pres = (int *)malloc(sizeof(int) * MAX); //暂时存反向的路径，因为得到的路径是反向的 
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
    }
    
    ArcNode *p;
    int floor = 0; // 记录层数
    queue.head = queue.rear = -1;
    queue.rear++;
    queue.q[queue.rear].n = u;
    queue.q[queue.rear].id = 1;
    queue.q[queue.rear].pre = -1;
    visited[u] = 1;
    while (queue.head < queue.rear) {
        queue.head++;
        int tem = queue.q[queue.head].n;
        p = G->adjlist[tem].firstarc;
        while (p != NULL) {
            if (visited[p->adjvex] == 0) {
                queue.rear++;
                queue.q[queue.rear].n = p->adjvex;
                queue.q[queue.rear].id = p->id;
                queue.q[queue.rear].pre = queue.head;
                visited[p->adjvex] = 1;
                if (p->adjvex == v) { //找到目标点
                    index = queue.rear; // 记录目标点在队列中的下标
                    flag = 1;   //flag 置1表示找到 
                }
            }
            p = p->nextarc;
        }
    }
    
    if (flag != 1) { //找不到u到v的一条路径
        res = "Not found such a path"; 
    } else {
        int ix = index;
        int i = 0;
        while (ix != -1) {
            if (queue.q[ix].id == 1) {
                pres[i] = queue.q[ix].n;
                i++;
            }
            ix = queue.q[ix].pre; 
        }
        
        int  temindex = 0;
        int  flag = 0;
        char tem_str[500];
        int  count_len;
        for (int j = i - 1; j >= 0; j--) {
            int tempn = pres[j];
            count_len = 0;
            
            if (tempn == 0) {
                tem_str[count_len] = tempn % 10 + '0';
                count_len++;
            }
            while (tempn != 0) { 
                tem_str[count_len] = tempn % 10 + '0';
                tempn = tempn / 10;
                count_len++;
            } //此时得到的字符串为倒序 
            while (count_len > 0) { // 换成正序存进res 
                res[temindex] = tem_str[count_len - 1];
                count_len--;
                temindex++;
            }
            if (j > 0) {
                res[temindex] = '-';
                temindex++;
                res[temindex] = '>';
                temindex++;
            }
        }
        res[temindex] = '\0';
    }
    
    return res;
}
