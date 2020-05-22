#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <queue>
#include <stack>
#include <set>
using namespace std;

const int inf = 2147483647;

void init_graph(map<char, map<char, int> >& graph) {
	char a, b;
	int c;
	while (cin >> a >> b >> c) {
		graph[a][b] = c;
	}
}

void init_distance(map<char, int>& distance, map<char, map<char, int> >& graph, char start) {
	distance[start] = 0;
	map<char, map<char, int> >::iterator  ite;
	for (ite = graph.begin(); ite != graph.end(); ++ite) {
		if ((*ite).first != start) {
			distance[(*ite).first] = inf;
		}
	}
}

void init_parent(map<char, char>& parent, map<char, map<char, int> >& graph) {
	map<char, map<char, int> >::iterator  ite;
	for (ite = graph.begin(); ite != graph.end(); ++ite) {
		parent[(*ite).first] = '0';
	}	
}

// 仿函数 小根堆
struct cmp {
	bool operator()(pair<char, int>& a, pair<char, int>& b) {
		return a.second > b.second;
	}
};

// dijkstra 单源最短路径算法
void dijkstra(map<char, map<char, int> >& graph, map<char, char>& parent, map<char, int>& distance, char start) {
	// seen中的节点已经求出最短路径	
	set<char> seen;
	// 优先队列
	priority_queue<pair<char, int>, vector<pair<char, int> >, cmp> pqueue;
	pqueue.push(make_pair(start, 0));

	while (pqueue.size() > 0) {
		pair<char, int> e = pqueue.top();
		pqueue.pop();
		char vert  = e.first;
		int  dist  = e.second;
		seen.insert(vert);

		map<char, int>::iterator ite;
		for (ite = graph[vert].begin(); ite!= graph[vert].end(); ++ite) {
			// 下一节点
			char nextvert = (*ite).first;
			// 源点到下一节点的距离
			int  nextdist = dist + (*ite).second;
			// 如果还没求出最短路径，并且 当前距离 比 之前求出的距离 还要短，则更新 距离 和 父节点
			// 并将节点入队
			if (seen.count(nextvert) == 0 && nextdist < distance[nextvert]) {
				parent[nextvert]   = vert;
				distance[nextvert] = nextdist;
				pqueue.push(make_pair(nextvert, nextdist));
			}
		}
	}
}

void print_distance(map<char, int>& distance) {
	map<char, int>::iterator    ite;
	for (ite = distance.begin(); ite != distance.end(); ++ite) {
		cout << (*ite).first << " " << (*ite).second << endl;
	}
	cout << endl;
}

void print_path(map<char, char>& parent, char start) {
	// 利用栈输出最短路径
	stack<char>                 st;

	map<char, char>::iterator   ite;
	for (ite = parent.begin(); ite != parent.end(); ++ite) {
		char vert = (*ite).first;
		if (vert != start) {
			while (vert != start) {
				st.push(vert);
				vert = parent[vert];
			}
			cout << start << " ";
			while (st.size() > 0) {
				cout << st.top() << " ";
				st.pop();
			}
			cout << endl;
		}
	}
	cout << endl;
}

int main() {
	// graph[a][b]  得到 a b 之间的距离
	map<char, map<char, int> > graph;
	// parent[a]    到达 a 的前一个节点
	map<char, char>            parent;
	// distance[a]  到达 a 的最短距离
	map<char, int>             distance;
	
	// 源点 初始化
	char start = 'a';
	init_graph(graph);
	init_distance(distance, graph, start);
	init_parent(parent, graph);
	
	dijkstra(graph, parent, distance, start);

	print_distance(distance);
	print_path(parent, start);
	return 0;
}