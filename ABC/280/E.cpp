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
	namespace _280 {
		using namespace std;
		// •ûj

		class E {
		public:

			static long inverse(long val, long mask)
			{
				long a = mask;
				long b = val % mask;
				long x = 1;
				long x1 = 0;
				long y = 0;
				long y1 = 1;
				while (b > 0)
				{
					long q = a / b;
					long r = a % b;
					long x2 = (mask + x - (q * x1) % mask) % mask;
					long y2 = (mask + y - (q * y1) % mask) % mask;
					a = b;
					b = r;
					x = x1;
					x1 = x2;
					y = y1;
					y1 = y2;
				}
				return y;
			}

			static void solve() {
				READ_LONG(n);
				READ_LONG(p);

				long mask = 998244353;
				long reverseProbability = (p * inverse(100, mask)) % mask;
				long reverseNotProbability = ((100 - p) * inverse(100, mask)) % mask;

				vector<long> dp(n + 1);
				dp[0] = 0;
				dp[1] = 1;

				for (long i = 2; i <= n; i++) {
					dp[i] = (reverseProbability * (1 + dp[i - 2])) % mask + (reverseNotProbability * (1 + dp[i - 1])) % mask;
					dp[i] %= mask;
				}

				WRITE_LINE(dp[n]);
			}
		};
	}
}

int main() {
	ABC::_280::E::solve();
}