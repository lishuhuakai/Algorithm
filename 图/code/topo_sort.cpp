#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <functional>
using namespace std;

/**
 * 这里的图使用邻接矩阵来表示,如果采用邻接表的话,可能会更加简单一点.
 */

const int MAX_NV = 100;	/* 顶点的最大值 */
using weight = int;
const int GRAPH_INF = INT_MAX / 2;

/**
 * @struct 图, 用邻接矩阵来表示图.
 */
struct Graph {
	int numOfVertexes; /* 顶点的数目 */
	int numOfEdges;	/* 边的数目 */
	weight matrix[MAX_NV][MAX_NV];
};

Graph g;
int topological[MAX_NV]; /* 拓扑排序的结果 */

/**
 * @brief 对图进行拓扑排序
 * @param[in] g 图
 * @return 如果排序成功,返回ture,否则返回false
 */
bool topo_sort(const Graph& g) 
{
	int n = g.numOfVertexes; /* 顶点的数目 */
	int degree[MAX_NV];
	int count = 0;
	queue<int> container;

	std::fill(degree, degree + n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g.matrix[i][j] < GRAPH_INF) {
				degree[j]++; /* 顶点j的入度加1 */
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		if (degree[i] == 0) container.push(i); /* 如果顶点i不存在依赖,那么入队列 */
	}

	while (!container.empty()) {
		int v = container.front(); 
		container.pop();
		topological[count++] = v; /* 排序成功 */
		for (int i = 0; i < n; i++) {
			if (g.matrix[v][i] < GRAPH_INF) {
				if (--degree[i] == 0) container.push(i); /* 解除依赖 */
			}
		}
	}

	return count == n;
	/* 如果存在环的话,不可能排序成功 */
}