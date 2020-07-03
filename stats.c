#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"




//----�ڽӱ�Ļ��������㷨------------------------------------
AdjGraph* CreateAdj(char name[])    //�����ڽӱ�
{
    AdjGraph *G;
	FILE     *fp;
	if (!(fp = fopen(name, "r"))) {
		printf("Can not open %s\n", name);
		exit(0);
	}

	int i;
	ArcNode *p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (i = 0; i < MAX; i++)						//���ڽӱ�������ͷ�ڵ��ָ�����ó�ֵ
		G->adjlist[i].firstarc = NULL;

	int u, v;
	int weight;

	while (!feof(fp)) {
		fscanf(fp, "%d%d%d\n", &u, &v, &weight);
		p = (ArcNode*)malloc(sizeof(ArcNode));	//����һ���ڵ�p
		p->adjvex = v;
		p->weight = weight;
		p->nextarc = G->adjlist[u].firstarc;	//����ͷ�巨����ڵ�p
		G->adjlist[u].firstarc = p;
	}
	fclose(fp);
	G->n = numberOfVertices(name);
	G->e = numberOfEdges(name);
	return G;
}
void DispAdj(AdjGraph* G)	//����ڽӱ�G
{
	ArcNode* p;
	for (int i = 0; i < MAX; i++)
	{
		p = G->adjlist[i].firstarc;
		printf("%3d: ", i);
		while (p != NULL)
		{
			printf("%3d[%d]��", p->adjvex, p->weight);
			p = p->nextarc;
		}
		printf("��\n");
	}
}
void DestroyAdj(AdjGraph* G)	//����ͼ���ڽӱ�
{
	ArcNode* pre, * p;
	for (int i = 0; i < MAX; i++)		//ɨ�����еĵ�����
	{
		pre = G->adjlist[i].firstarc;	//pָ���i����������׽ڵ�
		if (pre != NULL)
		{
			p = pre->nextarc;
			while (p != NULL)			//�ͷŵ�i������������б߽ڵ�
			{
				free(pre);
				pre = p; p = p->nextarc;
			}
			free(pre);
		}
	}
	free(G);						//�ͷ�ͷ�ڵ�����
}
//------------------------------------------------------------





//�������ļ���Ϊͼ��ʶ���� `char` ���飬����ͼ�бߵ�����
int numberOfEdges(char name[])
{
	FILE* fp;
	char buf[50];
	int e;      //����
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

//����ͼ�ж��������
int numberOfVertices(char name[])
{
	int node;    //������
	node = 0;
	int v, u;
	int weight;
	int* Vnode = (int*)malloc(sizeof(int) * 410000);         //��¼Vnode[i]�Ƿ���ڵı�־����
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

//����ͼ�� Freeman's Network Centrality ֵ
float freemanNetworkCentrality(char name[])
{
    return 0;
}

//����ͼ�� Closeness Centrality ֵ
float closenessCentrality(char name[], int node)
{
    return 0;
}

