#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "mylib.h" 




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
	for (i = 0; i < MAX; i++) {						//���ڽӱ�������ͷ�ڵ��ָ�����ó�ֵ
		G->adjlist[i].firstarc = NULL;
	}
    
	int u, v;
	int weight;

	while (!feof(fp)) {
		fscanf(fp, "%d%d%d\n", &u, &v, &weight);
		// u,v�ѳ��ֹ������Ϊ1��Ϊ�����Ȩͼ��׼�� 
		visited[u] = 1;
		visited[v] = 1;
		p = (ArcNode*)malloc(sizeof(ArcNode));	//����һ���ڵ�p
		p->id = 1; 
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

AdjGraph *TransformGraph(AdjGraph *G) //�����Ȩͼ 
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
        // �����Ȩͼ���ҵ���һ���ڵ㣬�������Ȩֵ����һ������weight-1���ڵ� 
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
                    }//�ҵ�һ���յĿ��Դ洢�ڵ�ı�� 
                    if (k == temnum || visited[k] == 1) { // �ҵ��Ŀ��Դ�����ź�ԭ���ĵ��ų�ͻ 
                        k++;                               //�ýڵ����ѳ��ֹ���k++ 
                        goto loop;
                    }
                    ptem->adjvex = k;// ָ���µĽڵ� 
                    ptem->weight = 1;//���½ڵ��ȨֵΪ1 
                    ptem->id = 0;
                    pn = (ArcNode *)malloc(sizeof(ArcNode));//Ϊ�½ڵ㿪�ٿռ䣬�½ڵ���������һ���½ڵ� 
                    pn->nextarc = NULL;
                    G->adjlist[k].firstarc = pn;
                    ptem = pn;
                }
                ptem->adjvex = temnum;//weight-1���ڵ����ӽ��������һ���½ڵ�ָ��ԭ��p���ӵĽڵ� 
                ptem->weight = 1;
                ptem->id = 1;
            }
            
            p = p->nextarc;
        }
    }
    return G;
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
	int* Vnode = (int*)malloc(sizeof(int) * MAX);         //��¼Vnode[i]�Ƿ���ڵı�־����
	for (int i = 0; i < MAX; i++) { // ��ʼ�� 
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

