#ifndef STATS_H
#define STATS_H

#define INF 0x3f3f3f3f				//定义∞
				
#define MAX 10000000              //最大顶点个数



//以下定义邻接表类型
typedef struct ANode
{
	int adjvex;					//该边的邻接点编号
	struct ANode* nextarc;		//指向下一条边的指针
	int weight;					//该边的权值（用整型表示）
	int id;                    // 用于把带权图改造成无权图，1代表是原有节点，0代表是新增节点 
} ArcNode;						//边节点类型

typedef struct Vnode
{
	int count;					//存放顶点入度,仅仅用于拓扑排序
	ArcNode* firstarc;			//指向第一条边
} VNode;						//邻接表头节点类型

typedef struct
{
	VNode adjlist[MAX];		//邻接表头节点数组
	int n, e;					//图中顶点数n和边数e
} AdjGraph;						//完整的图邻接表类型

typedef struct QNode {
    int n;                  // 存放数据
    int pre;                //存放父点的下标 
    int id;              // 标记这个节点是否是通过改造有权图得到的，1为否，0为是 
}QNode;

typedef struct Queue {
    QNode q[MAX];
    int head;               // 队头指针
    int rear;               // 队尾指针 
}Queue; 

Queue queue;                //定义队列 
//int visited[MAX];           //定义标记数组 

//邻接表的基本运算算法
AdjGraph* CreateAdj(char name[]); //创建图的邻接表
void DispAdj(AdjGraph* G);	//输出邻接表G
void DestroyAdj(AdjGraph* G);	//销毁图的邻接表
AdjGraph *TransformGraph(AdjGraph *G); //改造带权图 


//接受以文件名为图标识符的 `char` 数组，返回图中边的数量
int numberOfEdges(char name[]);         

//返回图中顶点的数量
int numberOfVertices(char name[]);       

//返回图中 Freeman's Network Centrality 值
float freemanNetworkCentrality(char name[]);

//返回图中 Closeness Centrality 值
float closenessCentrality(char name[], int node);

#endif
