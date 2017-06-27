#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int sz = 1024;
int head[sz];

/**
 * @struct Edge 用于记录一条边.
 */
struct Edge {
	int to;	
	int weight;
	int next;		/* 用于记录同起点的下一条边的标号 */
};

Edge edges[sz];

/**
 * @brief 加边操作.
 * @param[in] u, v分别为起始节点的编号
 * @param[in] w 权重
 */
void add(int u, int v, int w)
{
	static int cnt = 0;
	edges[cnt].weight = w;
	edges[cnt].to = v;
	edges[cnt].next = head[u];
	head[u] = cnt++;
}

int main()
{
	int numOfEdges, numOfVertexes;
	int from, to, weight;
	memset(head, -1, sizeof(head));
	cin >> numOfEdges >> numOfVertexes;

	for (int i = 1; i <= numOfEdges; i++) {
		cin >> from >> to >> weight;
		add(from, to, weight);
		/*
		edges[i].to = to;
		edges[i].weight = weight;
		edges[i].next = head[from];
		head[from] = i;
		*/
	}

	/* traversal */
	for (int i = 1; i <= numOfVertexes; i++) {
		for (int k = head[i]; k != -1; k = edges[k].next) {
			cout << i << " " << edges[k].to << " " << edges[k].weight << endl;
 		}
	}
	getchar();
}