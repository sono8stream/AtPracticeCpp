#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

namespace Recommended {
	using namespace std;

	class ABC218_F {
	public:

		class Edge {
		public:
			int Id;
			int From;
			int To;
			int Length;

			Edge() {
				Id = -1;
				From = -1;
				To = -1;
				Length = 0;
			}

			Edge(int id, int from, int to) {
				Id = id;
				From = from;
				To = to;
				Length = 1;
			}
		};

		static void calcCosts(const vector<Edge>* graph, int* costs, const int size,
			int ignoreEdgeID = -1) {
			queue<int> que;
			memset(costs, -1, size * sizeof(int));
			costs[0] = 0;
			que.emplace(0);
			while (!que.empty()) {
				int now = que.front();
				que.pop();

				for (auto itr = graph[now].begin(); itr != graph[now].end(); ++itr) {
					const Edge e = *itr;
					if (e.Id == ignoreEdgeID) {
						continue;
					}

					if (costs[e.To] == -1) {
						costs[e.To] = costs[e.From] + e.Length;
						que.emplace(e.To);
					}
				}
			}
		}

		static void calcCriticalPath(const vector<Edge>* graph, const int* costs, const int size,
			set<int>& criticalPath) {
			criticalPath.clear();
			int last = size - 1;

			if (costs[last] == -1) {
				return;
			}

			int now = last;
			while (now != 0) {
				for (auto itr = graph[now].begin(); itr != graph[now].end(); ++itr) {
					int to = itr->To;
					if (costs[now] > costs[to]) {
						now = to;
						criticalPath.emplace(itr->Id);
						break;
					}
				}
			}
		}

		static void solve() {
			int n, m;
			cin >> n >> m;

			vector<Edge>* graph = new vector<Edge>[n];
			vector<Edge>* revGraph = new vector<Edge>[n];
			Edge* edges = new Edge[m];
			for (int i = 0; i < m; ++i) {
				int fromRaw, toRaw;
				cin >> fromRaw >> toRaw;
				int from = fromRaw - 1;
				int to = toRaw - 1;
				edges[i] = Edge(i, from, to);
				graph[from].emplace_back(Edge(i, from, to));
				revGraph[to].emplace_back(Edge(i, to, from));
			}

			int* originalCosts = new int[n];
			calcCosts(graph, originalCosts, n);
			set<int> criticalPath;
			calcCriticalPath(revGraph, originalCosts, n, criticalPath);

			int* res = new int[m];
			for (int i = 0; i < m; ++i) {
				if (criticalPath.find(i) == criticalPath.end()) {
					res[i] = originalCosts[n - 1];
				}
				else {
					int* tmpCosts = new int[n];
					calcCosts(graph, tmpCosts, n, i);
					res[i] = tmpCosts[n - 1];

					delete[] tmpCosts;
				}
			}

			for (int i = 0; i < m; ++i) {
				cout << res[i] << endl;
			}

			delete[] graph;
			delete[] revGraph;
			delete[] edges;
			delete[] originalCosts;
			delete[] res;
		}
	};
}

int main() {
	Recommended::ABC218_F::solve();
}