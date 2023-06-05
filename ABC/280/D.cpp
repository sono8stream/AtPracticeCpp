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

		class D {
		public:

			static void getFactors(long k, map<long, long>& rFactors) {
				rFactors.clear();
				long maxItr = (long)sqrt(k) + 10;
				vector<bool> checked(maxItr, false);

				for (long i = 2; i < maxItr; i++) {
					if (checked[i]) {
						continue;
					}

					while (k % i == 0) {
						k /= i;
						if (rFactors.find(i) == rFactors.end()) {
							rFactors.emplace(i, 0);
						}
						rFactors[i]++;
					}

					for (long j = i; j < maxItr; j += i) {
						checked[j] = false;
					}
				}

				if (k > 1) {
					rFactors.emplace(k, 1);
				}
			}

			static void solve() {
				READ_LONG(k);

				map<long, long> factors;
				getFactors(k, factors);

				long res = 0;
				for (auto itr = factors.begin(); itr != factors.end(); itr++) {
					// ‘fˆö”‚ğw’è‚µ‚½ŒÂ”‚¾‚¯ŠÜ‚ŞÅ¬‚Ì’l‚ğ“ñ•ª’Tõ‚Å‹‚ß‚é
					long bottom = 1;
					long top = k;
					while (bottom + 1 < top) {
						long mid = (bottom + top) / 2;

						long current = itr->first;
						long count = 0;
						while (current <= mid) {
							count += mid / current;
							current *= itr->first;
						}

						if (count >= itr->second) {
							top = mid;
						}
						else {
							bottom = mid;
						}
					}	

					res = max(res, top);
				}

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_280::D::solve();
}