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

		class C {
		public:


			static void solve() {
				READ_INT(n);
				READ_INT(m);
				READ_LONG_ARRAY(arr, n);

				int first = m - 1;
				vector<long> sums(n, 0);
				for (int i = 0; i < m; i++) {
					sums[first] += arr[i];
				}
				for (int i = first + 1; i < n; i++) {
					sums[i] = sums[i - 1] + arr[i] - arr[i - m];
				}

				vector<long> scores(n, 0);
				for (int i = 0; i < m; i++) {
					scores[first] += arr[i] * (i + 1);
				}

				long res = scores[first];
				for (int i = first + 1; i < n; i++) {
					scores[i] = scores[i - 1] - sums[i - 1] + arr[i] * m;
					res = max(res, scores[i]);
				}

				WRITE_LINE(res);
			}
		};
	}
}

int main() {
	ABC::_267::C::solve();
}