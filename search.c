#include "search.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
int visited[MAX];
int path_DFS[MAX];      //DFS算法中纪录路径的数组
int path_putout_DFS[MAX];

#define INF 0xff33ff
int path_Dij[MAX];//最短长度数组，路径数组
int dist[MAX];//最短路径长度数组
int S[MAX];//标记数组
int path_putout_Dij[MAX];


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
	path_putout_Dij[0] = d ;
	for (i = 1; i <= d + 1; i++) {
		path_putout_Dij[i] = dist[d + 1 - i];
	}
}



char* shortestPath(int u, int v, char algorithm[], char name[])
{
}

