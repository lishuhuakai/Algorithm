#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int sz = 1024;

int head[sz];

struct Edge {
	int from;
	int weight;
	int to;
};

Edge edges[sz];

/**
 * @brief 排序函数,首先根据from从小到大排, from域相等的话, 根据to从小到大排,如果to域相等,根据weight从小到大排.
 * @param[in] lhs, rhs 左右两个需要比较的边.
 */
bool cmp(Edge& lhs, Edge& rhs) 
{
	if (lhs.from == rhs.from && lhs.to == rhs.to) return lhs.weight < rhs.weight;
	if (lhs.from == rhs.from) return lhs.to < rhs.to;
	return lhs.from < rhs.from;
}

int main()
{
	int numOfEdges, numOfVertexes;
	cin >> numOfEdges >> numOfVertexes;	/* 得到顶点的数目和边的数目 */

	for (int i = 0; i < numOfEdges; i++) {
		cin >> edges[i].from >> edges[i].to >> edges[i].weight;
	}
	sort(edges, edges + numOfEdges, cmp);
	
	/* 确定每一个顶点的起始边的编号 */
	head[edges[0].from] = 0;
	for (int i = 1; i < numOfEdges; i++) {
		if (edges[i].from != edges[i - 1].from) {
			head[edges[i].from] = i;
		}
	}

	for (int i = 1; i <= numOfVertexes; i++) {
		for (int k = head[i]; edges[k].from == i && k < numOfEdges; k++) {
			cout << edges[k].from << " " << edges[k].to << " " << edges[k].weight << endl;
		}
	}

	for (int i = 0; i <= numOfVertexes; i++) {
		cout << head[i] << " ";
	}
	cout << endl;
	getchar();
}