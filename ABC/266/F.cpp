#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>

#define READ_INT(var) int var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;
#define long long long

namespace ABC {
	namespace _266 {
		using namespace std;
		// 閉路を検出し、閉路とそれ以外をグルーピング

		class UnionFind {
		public:
			UnionFind(int size)
				:parents(size), sizes(size, 1), ranks(size, 0) {
				for (int i = 0; i < size; i++) {
					parents[i] = i;
				}
			}

			bool isRoot(const int pos) {
				return pos == parents[pos];
			}

			int getRoot(const int pos) {
				int now = pos;
				while (!isRoot(now)) {
					now = parents[now];
				}

				parents[pos] = now;
				return now;
			}

			int getSize(const int pos) {
				return sizes[getRoot(pos)];
			}

			void unite(int x, int y) {
				int rootX = getRoot(x);
				int rootY = getRoot(y);

				if (rootX == rootY) {
					return;
				}

				if (ranks[rootX] < ranks[rootY]) {
					swap(rootX, rootY);
				}

				parents[rootY] = rootX;
				if (ranks[rootX] == ranks[rootY]) {
					ranks[rootX]++;
				}

				sizes[rootX] += sizes[rootY];
			}

		private:
			vector<int> parents, sizes, ranks;
		};

		class F {
		public:

			static void findLoop(int n, vector<set<int>> graph, vector<bool>& onLoop) {
				queue<int> que;
				for (int i = 0; i < n; i++) {
					if (1 == graph[i].size()) {
						que.emplace(i);
					}
				}

				while (!que.empty()) {
					int now = que.front();
					que.pop();
					for (auto itr = graph[now].begin(); itr != graph[now].end(); itr++) {
						int to = *itr;

						set<int> hoge;
						graph[to].erase(now);
						if (graph[to].size() == 1) {
							que.emplace(to);
						}
					}
				}

				for (int i = 0; i < n; i++) {
					if (1 < graph[i].size()) {
						onLoop[i] = true;
					}
				}
			}

			static void solve() {
				READ_INT(n);
				READ_GRAPH_NODIRE(graph, n, n);

				vector<bool> onLoop(n, false);
				findLoop(n, graph, onLoop);

				UnionFind uf(n);
				vector<bool> visited(n, false);
				queue<int> que;
				int loopPos;
				for (int i = 0; i < n; i++) {
					if (onLoop[i]) {
						loopPos = i;
						break;
					}
				}
				que.emplace(loopPos);
				visited[loopPos] = true;

				while (!que.empty()) {
					int now = que.front();
					que.pop();

					for (auto itr = graph[now].begin(); itr != graph[now].end(); itr++) {
						int to = *itr;
						if (visited[to]) {
							continue;
						}

						if (!onLoop[to]) {
							uf.unite(now, to);
						}

						visited[to] = true;
						que.emplace(to);
					}
				}

				READ_INT(q);
				for (int i = 0; i < q; i++) {
					int x, y;
					cin >> x >> y;

					int rx = uf.getRoot(x - 1);
					int ry = uf.getRoot(y - 1);

					if (rx == ry) {
						cout << "Yes" << endl;
					}
					else {
						cout << "No" << endl;
					}
				}
			}
		};
	}
}

int main() {
	ABC::_266::F::solve();
}