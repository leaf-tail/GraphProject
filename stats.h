#ifndef STATS_H
#define STATS_H

#define INF 0x3f3f3f3f				//�����
				
#define MAX 410000              //��󶥵����



//���¶����ڽӱ�����
typedef struct ANode
{
	int adjvex;					//�ñߵ��ڽӵ���
	struct ANode* nextarc;		//ָ����һ���ߵ�ָ��
	int weight;					//�ñߵ�Ȩֵ�������ͱ�ʾ��
} ArcNode;						//�߽ڵ�����

typedef struct Vnode
{
	int count;					//��Ŷ������,����������������
	ArcNode* firstarc;			//ָ���һ����
} VNode;						//�ڽӱ�ͷ�ڵ�����

typedef struct
{
	VNode adjlist[MAX];		//�ڽӱ�ͷ�ڵ�����
	int n, e;					//ͼ�ж�����n�ͱ���e
} AdjGraph;						//������ͼ�ڽӱ�����



//�ڽӱ�Ļ��������㷨
AdjGraph* CreateAdj(char name[]); //����ͼ���ڽӱ�
void DispAdj(AdjGraph* G);	//����ڽӱ�G
void DestroyAdj(AdjGraph* G);	//����ͼ���ڽӱ�


//�������ļ���Ϊͼ��ʶ���� `char` ���飬����ͼ�бߵ�����
int numberOfEdges(char name[]);         

//����ͼ�ж��������
int numberOfVertices(char name[]);       

//����ͼ�� Freeman's Network Centrality ֵ
float freemanNetworkCentrality(char name[]);

//����ͼ�� Closeness Centrality ֵ
float closenessCentrality(char name[], int node);

#endif
