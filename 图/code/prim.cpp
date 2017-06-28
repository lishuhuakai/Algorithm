#include <iostream>
#include <vector>
#include <functional>
#include <queue>
using namespace std;

const int MAX_NV = 100;	/* 顶点的最大值 */
using weight = int;

/**
 * @struct 图,用邻接矩阵来表示.
 */
struct Graph {
	int numOfVertexes; /* 顶点的数目 */
	int numOfEdges; /* 边的数目 */
	weight matrix[MAX_NV][MAX_NV];
};

Graph g;
bool contained[MAX_NV];	/* 用于标记顶点是否已经加入最小生成树 */

/**
 * @struct 边,一个辅助结构,方便于求最小生成树.
 */
struct Edge {
	int u;
	int v;
	weight w;
	Edge(int u, int v, int w): u(u), v(v), w(w) {}
	bool operator>(const Edge& rhs) {
		return w > rhs.w;
	}
};


/**
 * @brief prim算法求最小生成树
 * @param[in] g 图
 */
void prim(const Graph &g) 
{
	priority_queue<Edge, vector<Edge>, greater<Edge>> container;
	/**
	 * 关于上面的式子,vector<Edge>表示优先队列使用vector来实现, greater<Edge>表示从小
	 * 到大排序.
	 */
	int n = g.numOfVertexes; /* 顶点的数目 */
	int u = 0; /* 开始的顶点的标号为0 */
	int count = 0; /* 边的数目计数 */
	contained[0] = true;
	std::fill(contained, contained + n, false);

	while (count < n - 1) { /* n个顶点最多n - 1条边 */
		for (int v = 0; v < n; v++) {
			if (!contained[v]) { /* 顶点v未被加入生成树 */
				Edge e(u, v, g.matrix[u][v]);
				container.push(e);
			}
		}

		while (!container.empty()) {
			Edge e = container.top(); 
			container.pop();
			if (!contained[e.v]) { /* 顶点v未被加入生成树 */
				u = e.v;
				contained[u] = true;
				count++;
				break;
			}
		}
	}

}