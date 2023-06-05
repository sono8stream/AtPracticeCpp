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
	namespace _282 {
		using namespace std;
		// 方針

		class D {
		public:

			// 閉路の検出
			// groupsに2部グラフになっているグラフの数を蓄積していく
			static void dfs(int size, vector<vector<int>>& graph,vector<vector<long>>& groups) {
				vector<int> nums(size, -1);
				groups = vector<vector<long>>();

				for (int i = 0; i < size; i++) {
					if (nums[i] >= 0) {
						continue;
					}

					stack<vector<int>> stk;
					stk.emplace(vector<int>({ i,-1 }));
					bool isPair = false;
					long odds = 0;
					long evens = 0;
					long edges = 0;

					while (!stk.empty()) {
						vector<int> now = stk.top();
						stk.pop();
						int pos = now[0];
						int from = now[1];
						if (nums[pos] >= 0) {
							// 閉路検出した

							if ((nums[from] + 1 - nums[pos]) % 2 != 0) {
								// 偶数長の閉路を検出
								isPair = true;
							}
							continue;
						}

						if (from == -1) {
							nums[pos] = 0;
						}
						else {
							nums[pos] = nums[from] + 1;
						}

						if (nums[pos] % 2 == 1) {
							odds++;
						}
						else {
							evens++;
						}

						for (int j = 0; j < graph[pos].size(); j++) {
							int to = graph[pos][j];

							if (from == to) {
								// 逆のパスならチェックしない
								continue;
							}

							stk.push(vector<int>({ to,pos }));
						}
						edges += graph[pos].size();
					}

					if (!isPair) {
						// 偶数長の閉路なら無視
						groups.emplace_back(vector<long>({ odds,evens,odds + evens,edges / 2 }));
					}
				}
			}

			static void solve() {
				READ_INT(n);
				READ_INT(m);

				vector<vector<int>> graph(n, vector<int>());
				for (int i = 0; i < m; i++) {
					READ_INT(u);
					READ_INT(v);
					graph[u - 1].emplace_back(v - 1);
					graph[v - 1].emplace_back(u - 1);
				}

				vector<vector<long>> groups;
				dfs(n, graph, groups);
				long total = 0;
				for (int i = 0; i < groups.size(); i++) {
					total += groups[i][2];
				}
				if (total != n) {
					WRITE_LINE(0);
					return;
				}

				long res = 0;
				for (int i = 0; i < groups.size(); i++) {
					total -= groups[i][2];
					res += groups[i][2] * total;
					res += groups[i][0] * groups[i][1];
					res -= groups[i][3];// 既に存在する組み合わせは除く
				}

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_282::D::solve();
}