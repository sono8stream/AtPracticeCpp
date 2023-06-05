#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <cstring>

#define READ_INT(var) int var;std::cin>>var;
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;
#define long long long

namespace ABC {
	namespace _266 {
		using namespace std;

		class D {
		public:

			static void solve() {
				READ_INT(n);
				vector<int> ts(n);
				vector<int> xs(n);
				vector<int> as(n);
				for (int i = 0; i < n; i++) {
					cin >> ts[i] >> xs[i] >> as[i];
				}

				int maxT = 100000;
				vector<vector<long>> dp(maxT + 5, vector<long>(5, -1));
				dp[0][0] = 0;
				int xI = 0;
				for (int i = 0; i <= maxT; i++) {
					if (xI < n && ts[xI] == i) {
						if (dp[i][xs[xI]] != -1) {
							dp[i][xs[xI]] += as[xI];
						}
						xI++;
					}

					for (int j = 0; j < 5; j++) {
						if (dp[i][j] == -1) {
							continue;
						}

						if (j - 1 >= 0) {
							dp[i + 1][j - 1] = max(dp[i + 1][j - 1], dp[i][j]);
						}
						dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
						if (j + 1 <5) {
							dp[i + 1][j + 1] = max(dp[i + 1][j +1], dp[i][j]);
						}
					}
				}
				
				long res = 0;				
				for (int i = 0; i < 5; i++) {
					res = max(res, dp[maxT][i]);
				}
				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_266::D::solve();
}