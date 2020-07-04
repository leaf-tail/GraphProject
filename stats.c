#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"




//----邻接表的基本运算算法------------------------------------
AdjGraph* CreateAdj(char name[])    //建立邻接表
{
	AdjGraph* G;
	FILE* fp;
	if (!(fp = fopen(name, "r"))) {
		printf("Can not open %s\n", name);
		exit(0);
	}

	int i;
	ArcNode *p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (i = 0; i < MAX; i++)						//给邻接表中所有头节点的指针域置初值
		G->adjlist[i].firstarc = NULL;

	int u, v;
	int weight;

	while (!feof(fp)) {
		fscanf(fp, "%d%d%d\n", &u, &v, &weight);
		p = (ArcNode*)malloc(sizeof(ArcNode));	//创建一个节点p
		p->adjvex = v;
		p->weight = weight;
		p->nextarc = G->adjlist[u].firstarc;	//采用头插法插入节点p
		G->adjlist[u].firstarc = p;
	}
	fclose(fp);
	G->n = numberOfVertices(name);
	G->e = numberOfEdges(name);
	return G;
}
void DispAdj(AdjGraph* G)	//输出邻接表G
{
	ArcNode* p;
	for (int i = 0; i < MAX; i++)
	{
		p = G->adjlist[i].firstarc;
		printf("%3d: ", i);
		while (p != NULL)
		{
			printf("%3d[%d]→", p->adjvex, p->weight);
			p = p->nextarc;
		}
		printf("∧\n");
	}
}
void DestroyAdj(AdjGraph*& G)	//销毁图的邻接表
{
	ArcNode* pre, * p;
	for (int i = 0; i < MAX; i++)		//扫描所有的单链表
	{
		pre = G->adjlist[i].firstarc;	//p指向第i个单链表的首节点
		if (pre != NULL)
		{
			p = pre->nextarc;
			while (p != NULL)			//释放第i个单链表的所有边节点
			{
				free(pre);
				pre = p; p = p->nextarc;
			}
			free(pre);
		}
	}
	free(G);						//释放头节点数组
}
//------------------------------------------------------------





//接受以文件名为图标识符的 `char` 数组，返回图中边的数量
int numberOfEdges(char name[])
{
	FILE* fp;
	char buf[50];
	int e;      //边数
	e = 0;
	if (!(fp = fopen(name, "r"))) {
		printf("Can not open %s\n", name);
		exit(0);
	}

	while (!feof(fp)) {
		fgets(buf, 50, fp);
		e++;
	}

	fclose(fp);
	return e;

}

//返回图中顶点的数量
int numberOfVertices(char name[])
{
	int node;    //顶点数
	node = 0;
	int v, u;
	int weight;
	int* Vnode = (int*)malloc(sizeof(int) * 410000);         //纪录Vnode[i]是否存在的标志数组
	memset(Vnode, 0, sizeof(Vnode));
	FILE* fp;
	char buf[50];
	if (!(fp = fopen(name, "r"))) {
		printf("Can not open %s\n", name);
		exit(0);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d%d%d\n", &v, &u, &weight);
		if (Vnode[v] == 0) {
			Vnode[v] = 1;
			node++;
		}
		if (Vnode[u] == 0) {
			Vnode[u] = 1;
			node++;
		}
	}

	fclose(fp);
	free(Vnode);
	return node;
}

//返回图中 Freeman's Network Centrality 值
int freemanNetworkCentrality(char name[])
{

}

//返回图中 Closeness Centrality 值
int closenessCentrality(char name[])
{

}

