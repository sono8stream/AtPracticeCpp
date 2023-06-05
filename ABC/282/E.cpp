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
		// •ûj

		class Val {
		public:
			int val;
			int left;
			int right;
			Val(int val, int left, int right) :val(val), left(left), right(right) {}
			bool operator< ( const Val& v2) const {
				return val < v2.val;
			};
			bool operator> (const Val& v2) const {
				return val > v2.val;
			};
		};

		class E {
		public:

			// •Â˜H‚ÌŒŸo
			// groups‚É2•”ƒOƒ‰ƒt‚É‚È‚Á‚Ä‚¢‚éƒOƒ‰ƒt‚Ì”‚ð’~Ï‚µ‚Ä‚¢‚­
			static long getPow(long a, long b, long mask) {
				long pow = a;
				long res = 1;
				while (b > 0) {
					if (b % 2 == 1) {
						res *= pow;
						res %= mask;
					}

					pow *= pow;
					pow %= mask;
					b /= 2;
				}
				return res;
			}

			static long getVal(long a, long b,long mask) {
				long left = getPow(a, b, mask);
				long right = getPow(b, a, mask);
				return (left + right) % mask;
			}

			static void solve() {
				READ_LONG(n);
				READ_LONG(m);
				READ_LONG_ARRAY(arr, n);

				priority_queue<Val> que;
				vector<bool> used(n, false);
				used[0] = true;
				for (int i = 1; i < n; i++) {
					long val = getVal(arr[0], arr[i], m);
					que.emplace(val, 0, i);
				}

				long res = 0;
				while (!que.empty()) {
					Val val = que.top();
					que.pop();

					if (used[val.right]) {
						continue;
					}

					used[val.right] = true;
					res += val.val;

					for (int i = 0; i < n; i++) {
						if (used[i]) {
							continue;
						}

						long nextVal = getVal(arr[val.right], arr[i], m);
						que.emplace(nextVal, val.right, i);
					}
				}

				/*priority_queue<Val,vector<Val>,greater<Val>> que;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (i == j) {
							continue;
						}

						long pow = getVal(arr[i], arr[j], m);
						que.emplace(pow, i, j);
					}
				}*/

				/*vector<bool> used(n);
				vector<int> remain(n, n - 1);
				long res = 0;
				while (!que.empty()) {
					Val now = que.top();
					que.pop();

					if (used[now.left] || used[now.right]) {
						continue;
					}

					remain[now.left]--;
					if (remain[now.left] == 0) {
						res += now.val;
						used[now.left] = true;
					}
				}*/

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_282::E::solve();
}