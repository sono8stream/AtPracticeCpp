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
#define READ_INT_ARRAY(var,length) vector<int> var(length);for(int i=0;i<length;i++){std::cin>>var[i];｝
#define READ_LONG_ARRAY(var,length) vector<long> var(length);for(int i=0;i<length;i++){std::cin>>var[i];}
#define READ_GRAPH_NODIRE(var,length,edges) vector<set<int>> var(length);for(int i=0;i<edges;i++){int u,v;std::cin>>u>>v;var[u-1].insert(v-1);var[v-1].insert(u-1);}
#define READ_STR(s) std::string s;std::cin>>s;
#define WRITE_LINE(x) std::cout<<x<<std::endl;

namespace ABC {
	namespace _280 {
		using namespace std;
		// 方針
		// そもそも、ハニカム構造での2点間の距離はmax(|X|,|Y|,|X-Y|)で表される。
		// これは3次元空間（X,Y,X-Y）によるチェビシェフ距離に変換できる←ここに気づけなかった
		// この3次元空間内でD*D*Dの立方体内に含まれる点どうしのチェビシェフ距離は必ずD以下となるため、問題文の条件判定ができるようになる
		// いや、結局D*D*D内の2点間でもZ座標がDを超える可能性がある
		// 各軸は独立に考えられるので、X,Yを固定してZ方向のみ尺取りで求めればよい
		// 重複を防ぐには、各軸について最小の座標を固定しながら動かす
		// 端にある点は最もインデックスが小さいものを固定するようにする

		class G {
		public:

			static void solve() {
				READ_LONG(n);
				READ_LONG(d);

				vector<long> xs(n, 0), ys(n, 0);
				vector<vector<long>> poses;
				for (int i = 0; i < n; i++) {
					cin >> xs[i] >> ys[i];
					vector<long> pos{ xs[i],ys[i],xs[i] - ys[i] };
					poses.emplace_back(pos);
				}

				long mask = 998244353;

				vector<long> pows(n + 10);
				pows[0] = 1;
				for (int i = 1; i < pows.size(); i++) {
					pows[i] = pows[i - 1] * 2;
					pows[i] %= mask;
				}

				long res = 0;

				for (int i = 0; i < n; i++) {// X座標最小の点
					for (int j = 0; j < n; j++) {// Y座標最小の点
						// iがX座標最小でなければスキップ
						if (poses[j][0] < poses[i][0]
							|| (poses[i][0] == poses[j][0] && j < i)) {
							continue;
						}
						// jがY座標最小でなければスキップ
						if (poses[i][1] < poses[j][1]
							|| (poses[i][1] == poses[j][1] && i < j)) {
							continue;
						}
						// 2点のみで条件を満たさない場合もスキップ
						if (poses[j][0] > poses[i][0] + d
							|| poses[i][1] > poses[j][1] + d) {
							continue;
						}

						vector<int> ids;
						for (int k = 0; k < n; k++) {
							// X方向に範囲内に無い場合はスキップ
							if (poses[k][0]<poses[i][0] || poses[k][0]>poses[i][0] + d
								|| (poses[k][0] == poses[i][0] && k < i)) {
								continue;
							}
							// Y方向に範囲内に無い場合はスキップ
							if (poses[k][1]<poses[j][1] || poses[k][1]>poses[j][1] + d
								|| (poses[k][1] == poses[j][1] && k < j)) {
								continue;
							}

							ids.emplace_back(k);
						}

						sort(ids.begin(), ids.end(), [&](int a, int b) {
							return poses[a][2] < poses[b][2] || (poses[a][2] == poses[b][2] && a < b);
							});

						// 尺取り
						int right = 0;// Z座標最小値
						for (int left = 0; left < ids.size(); left++) {
							int id = ids[left];
							// 固定した2点が条件を満たさない場合はスキップ
							if (poses[i][2]<poses[id][2] || poses[i][2]>poses[id][2] + d
								|| (poses[i][2] == poses[id][2] && i < id)) {
								continue;
							}
							if (poses[j][2]<poses[id][2] || poses[j][2]>poses[id][2] + d
								|| (poses[j][2] == poses[id][2] && j < id)) {
								continue;
							}

							while (right < ids.size() && poses[ids[right]][2] <= poses[id][2] + d) {
								right++;
							}

							int num = right - left - set<int>({ i, j, id }).size();
							res += pows[num];
							res %= mask;
						}
					}
				}

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_280::G::solve();
}