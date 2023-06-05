#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <cmath>

#define long long long

#define READ_INT(var) int var;std::cin>>var;
#define READ_LONG(var) long var;std::cin>>var;
#define READ_DOUBLE(var) double var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;

namespace ABC {
	namespace _292 {
		using namespace std;
		// 方針
		// トポロジカルソートして逆からたどる

		class E {
		public:

			static void topologicalSort(const vector<set<int>>& graph, vector<int>& order) {
				int len = graph.size();
				vector<int> inCounts(len, 0);
				for (int i = 0; i < len; i++) {
					for (auto to = graph[i].begin(); to != graph[i].end(); to++) {
						inCounts[*to]++;
					}
				}

				queue<int> inZeros;
				// 初期値
				for (int i = 0; i < len; i++) {
					if (0 == inCounts[i]) {
						inZeros.emplace(i);
					}
				}

				// ソート
				order.clear();
				while (!inZeros.empty()) {
					int current = inZeros.front();
					inZeros.pop();
					order.emplace_back(current);

					for (auto to = graph[current].begin(); to != graph[current].end(); to++) {
						inCounts[*to]--;
						if (0 == inCounts[*to]) {
							inZeros.emplace(*to);
						}
					}
				}
			}

			static void solve() {
				READ_INT(n);
				READ_INT(m);

				vector<set<int>> graph(n, set<int>());

				class Edge {
				public:
					int from;
					int to;
					Edge(int f, int t) :from(f), to(t) {}
				};

				for (int i = 0; i < m; i++) {
					READ_INT(u);
					READ_INT(v);
					graph[u - 1].emplace(v - 1);
				}

				int res = 0;
				for (int i = 0; i < n; i++) {
					// BFS
					queue<int> que;
					vector<bool> visited(n, false);
					que.emplace(i);
					while (!que.empty()) {
						int now = que.front();
						que.pop();
						if (visited[now]) {
							continue;
						}
						visited[now] = true;

						for (auto toItr = graph[now].begin(); toItr != graph[now].end(); toItr++) {
							int to = *toItr;
							if (visited[to]) {
								continue;
							}

							que.push(to);
						}
					}

					int count = 0;
					for (int j = 0; j < n; j++) {
						if (visited[j]) {
							count++;
						}
					}
					res += count - 1;// 自分自身への接続は除く
				}

				res -=m;// 初期値分は引いておく

				WRITE_LINE(res);

				/*
				vector<int> order;
				topologicalSort(graph, order);

				vector<int> outCounts(n, 0);
				int res = 0;
				for (int i = n - 1; i >= 0; i--) {
					int now = order[i];

					for (auto to = graph[now].begin(); to != graph[now].end(); to++) {
						for (auto to2 = graph[*to].begin(); to2 != graph[*to].end(); to2++) {
							graph[now].emplace(*to2);
						}
					}

					res += graph[now].size();
				}
				// 初期からあるものは除く
				res -= m;

				WRITE_LINE(res);
				*/


			}
		};
	}
}

int main() {
	ABC::_292::E::solve();
}