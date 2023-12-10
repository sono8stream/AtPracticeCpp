#include <iostream>
#include <unordered_set>
#include <set>
#include <unordered_map>
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

#define READ_ARRAY_TO(var,length) for(int i=0;i<length;i++){std::cin>>var[i];}

#define WRITE_LINE(x) std::cout<<x<<std::endl;

namespace ABC {
	namespace _331 {
		using namespace std;
		// 方針
		// 最も高い組み合わせから順に見ていき、初めて相性の悪い組み合わせでなくなったものを選ぶ

		class Dish {
			// 価格とIDを保持
		public:
			int price;
			int id;
			Dish() :price(0), id(0) {
			}
			Dish(int price, int id) :price(price), id(id) {
			}
			bool operator<(const Dish& another) const {
				return this->price < another.price;
			}
			bool operator>(const Dish& another) const {
				return this->price > another.price;
			}

			// 代入演算子
			Dish& operator=(const Dish& another) {
				this->price = another.price;
				this->id = another.id;
				return *this;
			}

			static bool greater(const Dish& d1, const Dish& d2) {
				return d1.price > d2.price;
			}
		};

		class E {
		public:
			static const int ARR_MAX = 100000;

			E() {
			}

			void solve() {
				// サイズが大きいのでグローバルに確保
				static Dish mains[ARR_MAX];// メインディッシュの価格
				static Dish subs[ARR_MAX];// 副菜の価格

				READ_INT(n);
				READ_INT(m);
				READ_INT(l);

				for (int i = 0; i < n; i++) {
					READ_INT(price)
						mains[i] = Dish(price, i);
				}
				for (int i = 0; i < m; i++) {
					READ_INT(price)
						subs[i] = Dish(price, i);
				}

				// 相性の悪い組み合わせを保持
				map<int,set<int>> badChoices;
				for (int i = 0; i < l; i++) {
					READ_INT(c);
					READ_INT(d);
					badChoices[c - 1].insert(d - 1);
				}

				// 価格の高い順にソート
				sort(mains, mains + n, Dish::greater);
				sort(subs, subs + m, Dish::greater);

				// 高い順に定食価格を取得した場合のl+1個目の定食価格を二分探索で求める
				int low = 0;// 満たす方
				int high = mains[0].price + subs[0].price + 1;// 満たさない方
				while (high - low > 1) {
					int mid = (low + high) / 2;
					// 価格がmid以上のものがl+1個以上あるかどうかチェック
					int count = 0;
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < m; j++) {
							int price = mains[i].price + subs[j].price;
							if (price < mid) {
								break;
							}

							count++;
							if (count >= l + 1) {
								break;
							}
						}
						if (count >= l + 1) {
							break;
						}
					}

					if (count >= l + 1) {
						low = mid;
					}
					else {
						high = mid;
					}
				}

				int minPrice = low;// 最低価格。求める価格は必ずこれ以上
				// 価格の高いものを枝刈りしながら見ていく
				int resPrice = 0;
				int checkedCount = 0;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						int price = mains[i].price + subs[j].price;
						if (price < minPrice || price <= resPrice) {
							// 既にチェック済みの価格は枝刈りのためスキップ。
							// こうしないと最低価格が大量にあった場合にTLEする
							break;
						}

						if (badChoices.find(mains[i].id) == badChoices.end()
							|| badChoices[mains[i].id].find(subs[j].id) == badChoices[mains[i].id].end()) {
							// 悪い組み合わせでなければ価格を更新
							resPrice = max(resPrice, price);
						}
					}
				}

				WRITE_LINE(resPrice);
			}
		};
	}
}

int main() {
	ABC::_331::E solver;
	solver.solve();
}