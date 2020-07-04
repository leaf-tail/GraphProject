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
    
    for (int i = 0; i < MAX; i++) { //初始化全局标记数组
        visited[i] = 0; 
    }
    
    G = CreateAdj(name);
    char *res;
    
    if (strcmp(alogrithm, "DFS") == 0) {
        for (int i = 0; i < MAX; i++) { //初始化全局标记数组
            visited[i] = 0; 
        }
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
        for (int i = 0; i < MAX; i++) { //初始化全局标记数组
            visited[i] = 0; 
        }
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
            }  //此时得到的字符串为倒序 
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


void DFS(AdjGraph* G, int u, int v, int d)      //递归DFS（d纪录路径数，初次引用时值为-1 最终结果存在path_putout内）
{
	int w, i;
	ArcNode* p;
	visited[u] = 1;
	d++;
	path_DFS[d] = u;
	if (u == v) {
		path_DFS[d] = v;
		for (i = 0; i <= d; i++) {
			path_putout_DFS[i + 1] = path_DFS[i];
		}
		path_putout_DFS[0] = d + 1;       //纪录路径包含的顶点个数
		return;
	}
	p = G->adjlist[u].firstarc;
	while (p != NULL) {
		w = p->adjvex;
		if (visited[w] == 0) {
			DFS(G, w, v, d);
		}
		p = p->nextarc;
	}

}

void Dijkstra(AdjGraph* G, int u, int v)
{
	int mindis;
	int i, j, x;
	for (i = 0; i < MAX; i++) {
		S[i] = 0;                           //S[ ]置空
		dist[i] = INF;
	}
	ArcNode* p;
	p = G->adjlist[u].firstarc;

	while (p != NULL) {
		dist[p->adjvex] = p->weight;        //距离初始化
		p = p->nextarc;
	}

	for (i = 0; i < MAX; i++) {             //路径初始化
		if (dist[i] < INF) {
			path_Dij[i] = u;                    //顶点u到顶点i有边时，置顶点i的前驱节点为u
		}
		else {
			path_Dij[i] = -1;                   //顶点u到顶点i没有边时，置顶点i的前驱节点为-1
		}
	}
	S[u] = 1;
	path_Dij[u] = 0;                            //源点u放入S中
	for (i = 0; i < MAX; i++) {             //循环求出所有最短路径
		mindis = INF;                       //mindis置最大初值值
		for (j = 0; j < MAX; j++) {
			if (S[j] == 0 && dist[j] < mindis) {        //选取不在S中且具有最小最短路径长度的顶点x
				x = j;
				mindis = dist[j];
				//printf("%d  %d\n", mindis,x);

			}
		}
		S[x] = 1;                                      //顶点x放进S
		//printf("flag\n");

		p = G->adjlist[x].firstarc;
		while (p != NULL) {                            //修改不在S中的顶点的最短路径
			if (S[p->adjvex] == 0) {
				j = p->adjvex;
				//printf("%d\n", j);
				if (dist[x] + p->weight < dist[j]) {
					dist[j] = dist[x] + p->weight;
					path_Dij[j] = x;
				}
			}
			p = p->nextarc;
		}
	}
	//把答案路径的逆序存入dist，再将正序转入path_putout_Dij
	int d = 0;
	int k = 0;
	if (S[v] == 1) {

		d = 0;
		dist[d] = v;
		k = path_Dij[v];

		while (k != u) {
			d++;
			dist[d] = k;
			k = path_Dij[k];
		}
		d++; dist[d] = u;
	}
	d++;
	path_putout_Dij[0] = d ;                //p[0]存放路径中顶点个数
	for (i = 1; i <= d + 1; i++) {          //p[1]-p[d+1]存放路径
		path_putout_Dij[i] = dist[d + 1 - i];
	}
}

