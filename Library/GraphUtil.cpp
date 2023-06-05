#include <iostream>
#include <string>
#include <vector>
#include <queue>

namespace ABC {
	namespace Library {
		using namespace std;

		class GraphUtil {
		public:
			GraphUtil(){}

			static void Bfs(int n, const vector<vector<int>>& graph, vector<int>& distances) {
				queue<int> que;
				que.emplace(0);
				distances = vector<int>(-1);
				distances[0] = 0;

				while (!que.empty()) {
					int now = que.front();
					que.pop();

					for (int i = 0; i < graph[now].size(); i++) {
						int to = graph[now][i];

						if (distances[to] == -1) {
							distances[to] = distances[now] + 1;
							que.emplace(to);
						}
					}
				}
			}

		private:
			vector<int> parents, sizes, ranks;
		};
	}
}