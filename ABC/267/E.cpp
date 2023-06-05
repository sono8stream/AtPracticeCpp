#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>

#define READ_INT(var) int var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;
#define long long long

namespace ABC {
	namespace _267 {
		using namespace std;
		// •ûj
		// ‘å‚«‚¢’¸“_‚©‚ç‡‚Éˆ—

		class Score {
		public:
			long score;
			long index;

			Score() :score(0), index(0) {};

			Score(long score, long index):score(score),index(index) {
			};

			bool operator< (const Score& score2)const {
				return this->score < score2.score;
			};

			bool operator> ( const Score& score2)const {
				return this->score > score2.score;
			};
		};

		class E {
		public:


			static void solve() {
				READ_INT(n);
				READ_INT(m);
				READ_LONG_ARRAY(arr, n);
				READ_GRAPH_NODIRE(graph, n, m);

				vector<long> scores(n, 0);
				vector<bool> checked(n, false);
				priority_queue<Score,vector<Score>,greater<Score>> que;
				for (int i = 0; i < n; i++) {
					for (auto itr = graph[i].begin(); itr != graph[i].end(); itr++) {
						int to = *itr;
						scores[i] += arr[to];
					}

					que.emplace(scores[i], i);
				}

				long res = 0;
				while (!que.empty()) {
					const Score now = que.top();
					que.pop();
					if (checked[now.index]) {
						continue;
					}
					res = max(res, now.score);
					checked[now.index] = true;


					for (auto itr = graph[now.index].begin(); itr != graph[now.index].end(); ++itr) {
						int to = *itr;
						if (checked[to]) {
							continue;
						}

						scores[to] -= arr[now.index];
						que.emplace(scores[to], to);
					}

				}

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_267::E::solve();
}