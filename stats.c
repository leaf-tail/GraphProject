#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "mylib.h" 





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
	for (i = 0; i < MAX; i++) {						//给邻接表中所有头节点的指针域置初值
		G->adjlist[i].firstarc = NULL;
	}

	int u, v;
	int weight;

	while (!feof(fp)) {
		fscanf(fp, "%d%d%d\n", &u, &v, &weight);
    
		// u,v已出现过，标记为1，为改造带权图做准备 
		visited[u] = 1;
		visited[v] = 1;
		p = (ArcNode*)malloc(sizeof(ArcNode));	//创建一个节点p
		p->id = 1; 
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


AdjGraph* CreatereAdj(char name[])    //建立逆邻接表
{
	AdjGraph* G;
	FILE* fp;
	if (!(fp = fopen(name, "r"))) {
		printf("Can not open %s\n", name);
		exit(0);
	}

	int i;
	ArcNode* p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (i = 0; i < MAX; i++)						//给邻接表中所有头节点的指针域置初值
		G->adjlist[i].firstarc = NULL;

	int u, v;
	int weight;

	while (!feof(fp)) {
		fscanf(fp, "%d%d%d\n", &u, &v, &weight);
		p = (ArcNode*)malloc(sizeof(ArcNode));	//创建一个节点p
		p->adjvex = u;
		p->weight = weight;
		p->nextarc = G->adjlist[v].firstarc;	//采用头插法插入节点p
		G->adjlist[v].firstarc = p;
	}
	fclose(fp);
	G->n = 0;
	G->e = 0;
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
void DestroyAdj(AdjGraph* G)	//销毁图的邻接表
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

AdjGraph *TransformGraph(AdjGraph *G) //改造带权图 
{
    int temnum;
    int temp;
    int temweight;
    int k = 1;
    int *v = (int *)malloc(MAX * sizeof(int));
    
    for (int i = 0; i < MAX; i++) {
        v[i] = 0;
    }
    
    for (int i = 0; i < MAX; i++) {
        ArcNode *p = G->adjlist[i].firstarc;
        ArcNode *ptem;
        ArcNode *pn;
        // 改造带权图，找到第一个节点，如果它的权值大于一则增加weight-1个节点 
        while (p != NULL) {
            temnum = p->adjvex;
            temweight = p->weight;
            temp = i;
            ptem = p;
            if (p->weight > 1) {
                p->weight = 1;
            
                for (int j = 1; j < temweight; j++) {
                loop:
                    while (G->adjlist[k].firstarc != NULL) {
                        k++;
                    }//找到一个空的可以存储节点的编号  
                    if (k == temnum || visited[k] == 1) { // 找到的可以储存点编号和原来的点编号冲突  
                        k++;                               //该节点编号已出现过，k++  
                        goto loop;
                    }
                    ptem->adjvex = k;// 指向新的节点 
                    ptem->weight = 1;//与新节点间权值为1 
                    ptem->id = 0;
                    pn = (ArcNode *)malloc(sizeof(ArcNode));//为新节点开辟空间，新节点连接着下一个新节点 
                    pn->nextarc = NULL;
                    G->adjlist[k].firstarc = pn;
                    ptem = pn;
                }
                ptem->adjvex = temnum;//weight-1个节点增加结束，最后一个新节点指向原来p连接的节点
                ptem->weight = 1;
                ptem->id = 1;
            }
            
            p = p->nextarc;
        }
    }
    return G;
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
	int* Vnode = (int*)malloc(sizeof(int) * MAX);         //纪录Vnode[i]是否存在的标志数组
	for (int i = 0; i < MAX; i++) { // 初始化 
	    Vnode[i] = 0;
        }
	
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
float freemanNetworkCentrality(char name[])
{
	float result = 0;

	AdjGraph* G;
	G = CreateAdj(name);                //建立邻接表

	int i;
	int degree[MAX];                    //纪录度的数组
	for (i = 0; i < MAX; i++) {
		degree[i] = 0;
	}

	ArcNode* p;                         //出度
	for (i = 0; i < MAX; i++) {
		p = G->adjlist[i].firstarc;
		while (p != NULL) {
			degree[i]++;
			degree[p->adjvex]++;
			p = p->nextarc;
		}
	}
	 
	AdjGraph* reG;                       //入度
	reG = CreatereAdj(name);
	ArcNode* q;
	for (i = 0; i < MAX; i++) {
		q = reG->adjlist[i].firstarc;
		while (q != NULL) {
			degree[i]++;
			degree[q->adjvex]++;
			q = q->nextarc;
		}
	}

	for (i = 0; i < MAX; i++) {         
		degree[i] /= 2;
	}

	for (i = 0; i < MAX; i++) {              //去重
		p = G->adjlist[i].firstarc;
		q = reG->adjlist[i].firstarc;
		while (p != NULL && q != NULL) {
			int pnode = p->adjvex;
			int qnode = q->adjvex;
			if (pnode == qnode) {
				degree[i]--;
				p = p->nextarc;
				q = reG->adjlist[i].firstarc;
			}
			else {
				q = q->nextarc;
			}
		}
	}

	int tmp = degree[0];             //找最大度的点target
	int target = 0;
	for (i = 1; i < MAX; i++) {
		if (degree[i] > tmp) {
			tmp = degree[i];
			target = i;
		}
	}
	
	DestroyAdj(G);
	DestroyAdj(reG);
	
	int n;                           //求顶点个数
	n = numberOfVertices(name);

	tmp = 0;
	for (i = 0; i < MAX; i++) {
		if (i!=target) {
			if (degree[i] != 0) {
				tmp += degree[target] - degree[i];
			}		
		}
	}
	//printf("%d\n%d\n", target, n);

	result = tmp / 1.0;
	result = result / (n - 1) / (n - 2);
	return result;
}

//返回图中 Closeness Centrality 值
float closenessCentrality(char name[], int node)
{
    return 0;
}

