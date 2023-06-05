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
		// 方針

		class E {
		public:

			static void solve() {
				READ_INT(n);
				READ_INT(m);

				vector<vector<double>> xys(n,vector<double>(2,0));
				for (int i = 0; i < n; i++) {
					cin >> xys[i][0] >> xys[i][1];
				}

				vector<vector<double>> pqs(m, vector<double>(2, 0));
				for (int i = 0; i < m; i++) {
					cin >> pqs[i][0] >> pqs[i][1];
				}

				const int MAX_POS = 12 + 5;// 街と宝箱
				const int MAX_BOOST = 5;

				int allPat = 1 << (n + m);
				vector<vector<double>> dp(allPat, vector<double>(n + m + 1, 1e300));// 移動状態と現在地
				dp[0][0] = 0;
				for (int i = 0; i < allPat; i++) {
					bitset<MAX_POS> current(i);

					bitset<MAX_BOOST> boost(i >> n);
					int vel = 1 << boost.count();

					for (int j = 0; j <= n + m; j++) {
						double currentX = 0;
						double currentY = 0;

						if (0 == j) {
							if (0 == i) {
								currentX = 0;
								currentY = 0;
							}
							else {
								// 移動不可能
								continue;
							}
						}
						else {
							if (current[j - 1]) {
								if (j <= n) {
									currentX = xys[j - 1][0];
									currentY = xys[j - 1][1];
								}
								else {
									currentX = pqs[j - n - 1][0];
									currentY = pqs[j - n - 1][1];
								}
							}
							else {
								// 移動不可能
								continue;
							}
						}

						// 街へ移動
						for (int k = 0; k < n; k++) {
							if (current[k]) {
								// 既に訪れているのでスキップ
							}

							double xDist = xys[k][0] - currentX;
							double yDist = xys[k][1] - currentY;

							int nextState = (i | (1 << k));
							double next = dp[i][j] + sqrt(xDist * xDist + yDist * yDist) / vel;
							dp[nextState][k + 1] = min(dp[nextState][k + 1], next);
						}

						// 宝箱へ移動
						for (int k = 0; k < m; k++) {
							if (current[n + k]) {
								// 既に訪れているのでスキップ
							}

							double xDist = pqs[k][0] - currentX;
							double yDist = pqs[k][1] - currentY;

							int nextState = (i | (1 << (n + k)));
							double next = dp[i][j] + sqrt(xDist * xDist + yDist * yDist) / vel;
							dp[nextState][n + k + 1] = min(dp[nextState][n + k + 1], next);
						}
					}
				}

				// 結果計算
				double res = 1e300;
				int townPat = 1 << n;
				int tresurePat = 1 << m;
				for (int i = 0; i < tresurePat; i++) {
					int currentStatus = townPat - 1 + (i << n);
					bitset<MAX_POS> current(currentStatus);

					bitset<MAX_BOOST> boost(i);
					int vel = 1 << boost.count();

					for (int j = 1; j <= n + m; j++) {
						double xDist = 0;
						double yDist = 0;
						if (j <= n) {
							xDist = xys[j - 1][0];
							yDist = xys[j - 1][1];
						}
						else {
							xDist = pqs[j - n - 1][0];
							yDist = pqs[j - n - 1][1];
						}

						double next = dp[currentStatus][j] + sqrt(xDist * xDist + yDist * yDist) / vel;
						res = min(res, next);
					}
				}

				cout << setprecision(7) << res << endl;
			}
		};
	}
}

int main() {
	ABC::_274::E::solve();
}