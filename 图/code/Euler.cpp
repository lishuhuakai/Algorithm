#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int EDGE_MAX = 128;
const int VERTEX_MAX = 128;

typedef int edgeInfo;

/**
 * @struct 边
 */
struct Edge {
	int to; /* 终点编号 */
	edgeInfo info;	/* 边的信息,可以是标号,权重等等. */
	int next; /* 下一条同起点的边的编号 */
};

Edge edges[EDGE_MAX];
bool visited[EDGE_MAX];
int head[VERTEX_MAX];
queue<edgeInfo> path;


/**
 * @brief 从顶点u出发,寻找欧拉回路.
 * @param[in] u 顶点的编号 
 */
void findEulerCircuit(int u) 
{
	for (int k = head[u]; k != -1; k = edges[k].next) { /* 遍历从u出发的所有边 */
		if (!visited[k]) {
			visited[k] = true;	/* 这里需要注意,因为模拟的是无向边,所以走过一条边要标记两条 */
			if (k & 1) visited[k + 1] = true;
			else visited[k - 1] = true;
			findEulerCircuit(edges[k].to);
			path.push(edges[k].info); /* 回溯时记录边的信息 */
		}
	}
}

int main()
{
	int numOfEdges, numOfVertexes;
	int from, to;
	edgeInfo info;
	cin >> numOfEdges >> numOfVertexes;

	for (int i = 1; i <= numOfEdges; i++) { /* 为了方便编码,0号单元弃用 */
		/* 因为这里模拟的是无向图,所以略微麻烦,如果是有向图,一切都会变得简单很多 */
		cin >> from >> to >> info; /* 起始顶点标号,以及边的一些信息,如边的标号等等. */
		edges[2 * i - 1].to = to;
		edges[2 * i - 1].info = info;
		edges[2 * i - 1].next = head[from];
		head[from] = 2 * i - 1;

		edges[2 * i].to = from;
		edges[2 * i].info = info;
		edges[2 * i].next = head[to];
		head[to] = 2 * i;
	}
	memset(visited, false, sizeof(visited));
	findEulerCircuit(1);

	/* 输出边的信息 */
	while (!path.empty()) {
		cout << path.front() << " ";
		path.pop();
	}
	cout << endl;

	getchar();
}