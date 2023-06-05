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

namespace ARC {
	namespace _152 {
		using namespace std;
		// •ûj


		class B {
		public:

			static void solve() {
				READ_INT(n);
				READ_LONG(l);
				READ_LONG_ARRAY(arr, n);

				vector<long> rs(n, 0);
				for (int i = 0; i < n; i++) {
					rs[i] = (l - arr[i]) * 2;
				}

				sort(rs.begin(), rs.end());
				long res = 1e15;
				for (int i = 0; i < n; i++) {
					long lDelta = arr[i] * 2;

					if (lDelta < rs[0]) {
						long current = 2 * l + rs[0] - lDelta;
						res = min(res, current);
						continue;
					}

					int bottom = 0;
					int top = n;
					while (bottom + 1 < top) {
						int middle = (bottom + top) / 2;

						if (rs[middle] <= lDelta) {
							bottom = middle;
						}
						else {
							top = middle;
						}
					}

					long current = 2 * l + lDelta - rs[bottom];
					if (top < n) {
						long current2 = 2 * l + rs[top] - lDelta;
						current = min(current, current2);
					}

					res = min(res, current);
				}

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ARC::_152::B::solve();
}