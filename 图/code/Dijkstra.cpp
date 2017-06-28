#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <functional>
using namespace std;

const int MAX_NV = 100;	/* 顶点的最大值 */
using weight = int;

/**
 * @struct 图, 用邻接矩阵来表示图.
 */
struct Graph {
	int numOfVertexes; /* 顶点的数目 */
	int numOfEdges;	/* 边的数目 */
	weight matrix[MAX_NV][MAX_NV];
};


/**
 * @struct 距离,一个辅助结构,用于记录起点u到顶点v的距离,或者说到目前为止已知的最短距离
 */
struct Dist {
	int v; /* 路径的终点v,起点是u */
	int dist; /* 路径u -> v到目前为止已知的最短距离 */
	Dist(int u,int dist) : v(v), dist(dist) {}
	bool operator>(Dist& rhs) {
		return dist > rhs.dist;
	}
};

Graph g;
int dist[MAX_NV]; /* 记录起点到各个顶点的最小距离 */
int father[MAX_NV]; /* father[i]用于记录起点u通过最短路径到达顶点i时经过的中间顶点的编号 */

/**
 * @brief dijkstra算法求起点u到其余各个顶点的最短路径.
 * @param[in] g 图
 * @param[in] u 起点
 */
void dijkstra(const Graph& g, int u)
{
	priority_queue<Dist, vector<Dist>, greater<Dist>> container;
	int n = g.numOfVertexes; /* 顶点的数目 */
	std::fill(dist, dist + n, INT_MAX / 2);
	dist[u] = 0; /* 起点到自己的最短距离为0 */
	
	container.push(Dist(u, 0));
	while (!container.empty()) {
		Dist d = container.top(); 
		container.pop(); 
		for (int i = 0; i < n; ++i) {
			if (dist[d.v] + g.matrix[d.v][i] < dist[i]) {
				dist[i] = dist[d.v] + g.matrix[d.v][i];	/* 以节点v作为中间节点,从u到i距离更短 */
				father[i] = d.v; /* 从起点u到达i可以以v为中间节点 */
				container.push(Dist(dist[i], i));
			}
		}
	}
}

