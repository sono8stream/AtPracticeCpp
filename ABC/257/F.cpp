#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>
#include <vector>

namespace ABC {
	namespace _257 {
		using namespace std;



		class F {
		public:

			static const int infCost = 1e8;

			static void dijkstra(const vector<int>* graph, const int startId, int* costs, int vertices) {
				for (int i = 0; i < vertices; ++i) {
					costs[i] = infCost;
				}
				costs[startId] = 0;

				queue<int> que;
				que.emplace(startId);

				while (!que.empty()) {
					int now = que.front();
					que.pop();

					int nextCost = costs[now] + 1;
					for (int j = 0; j < graph[now].size(); ++j) {
						int to = graph[now][j];

						if (nextCost < costs[to]) {
							costs[to] = nextCost;
							que.emplace(to);
						}
					}
				}
			}

			static void solve() {
				int n, m;
				cin >> n >> m;
				int totalLength = n + 1;
				vector<int>* graph = new vector<int>[totalLength];

				for (int i = 0; i < m; ++i) {
					int u, v;
					cin >> u >> v;
					graph[u].emplace_back(v);
					graph[v].emplace_back(u);
				}

				int* goCosts = new int[totalLength];
				dijkstra(graph, 1, goCosts, totalLength);

				int* backCosts = new int[totalLength];
				dijkstra(graph, n, backCosts, totalLength);

				for (int i = 1; i <= n; ++i) {
					int res = goCosts[n];
					if (goCosts[0] != infCost && backCosts[i] != infCost) {
						res = min(res, goCosts[0] + backCosts[i]);
					}
					if (goCosts[i] != infCost && backCosts[0] != infCost) {
						res = min(res, goCosts[i] + backCosts[0]);
					}

					if (res == infCost) {
						cout << "-1 ";
					}
					else {
						cout << res << " ";
					}
				}

				delete[] graph;
				delete[] goCosts;
			}
		};
	}
}

int main() {
	ABC::_257::F::solve();
}