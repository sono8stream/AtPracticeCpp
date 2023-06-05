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
		// 1‰ñ•ª‚Ì—ÝÏ˜a‚ð‚Æ‚Á‚Ä‚¨‚­
		// —ÝÏ˜a‚ð—p‚¢‚ÄŠeI—¹ˆÊ’u‚²‚Æ‚ÉƒXƒRƒA‚ðŠi”[‚µ‚Ä‚¨‚­

		class D {
		public:


			static void solve() {
				READ_INT(n);
				READ_INT(m);
				READ_LONG_ARRAY(arr, n);

				long unassigned = -1e18;
				vector<vector<long>> dp(n, vector<long>(n + 1, unassigned));
				dp[0][0] = 0;
				dp[0][1] = arr[0] * 1;
				for (int i = 1; i < n; i++) {
					dp[i][0] = 0;
					for (int j = 1; j <= n; j++) {
						if (dp[i - 1][j - 1] == unassigned) {
							dp[i][j] = dp[i - 1][j];
						}
						else {
							dp[i][j] = max(dp[i - 1][j - 1] + arr[i] * j, dp[i - 1][j]);
						}
					}
				}

				long res = unassigned;
				for (int i = m-1; i < n; i++) {
					res = max(res, dp[i][m]);
				}

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_267::D::solve();
}