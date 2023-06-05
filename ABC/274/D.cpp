#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <algorithm>
#include <iomanip>

#define READ_INT(var) int var;std::cin>>var;
#define READ_DOUBLE(var) double var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;
#define long long long

namespace ABC {
	namespace _274 {
		using namespace std;
		// •ûj

		class D {
		public:

			static void solve() {
				READ_INT(n);
				READ_INT(x);
				READ_INT(y);
				READ_INT_ARRAY(arr, n);

				vector<int> xs, ys;
				for (int i = 0; i < n; i++) {
					if (i % 2 == 1) {
						ys.emplace_back(arr[i]);
					}
					else {
						xs.emplace_back(arr[i]);
					}
				}

				set<int> canX, canY;
				canX.insert(xs[0]);
				canY.insert(0);

				for (int i = 1; i < xs.size(); i++) {
					set<int> next;
					for (auto itr = canX.begin(); itr != canX.end(); itr++) {
						next.insert((*itr) + xs[i]);
						next.insert((*itr) - xs[i]);
					}
					canX = next;
				}

				for (int i = 0; i < ys.size(); i++) {
					set<int> next;
					for (auto itr = canY.begin(); itr != canY.end(); itr++) {
						next.insert((*itr) + ys[i]);
						next.insert((*itr) - ys[i]);
					}
					canY = next;
				}

				if (canX.end() != canX.find(x)
					&& canY.end() != canY.find(y)) {
					WRITE_LINE("Yes");
				}
				else {
					WRITE_LINE("No");
				}
			}
		};
	}
}

int main() {
	ABC::_274::D::solve();
}